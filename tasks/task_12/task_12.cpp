#include "..\..\terms\term.hpp"
#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <set>
#include <string>

using namespace std;
using namespace BoolApp;

random_device rd;
auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

// Литерал: пара (имя переменной, отрицание)
using Literal = std::pair<std::wstring, bool>;
using Conjunct = std::set<Literal>;

// Генерация случайного вектора функции
vector<bool> generate_vf(int n)
{
    vector<bool> f(1 << n);
    uniform_int_distribution<> dis(0, 1);
    for (auto b : f)
        b = dis(gen);
    return f;
}

wstring perfect_dnf(int amt_x, const vector<bool> &vf)
{
    wstring result;
    for (size_t i = 0; i < vf.size(); ++i)
    {
        if (vf[i])
        {
            wstring term;
            for (int j = 0; j < amt_x; ++j)
            {
                bool bit = (i >> (amt_x - j - 1)) & 1;
                if (!term.empty())
                    term += L"&";
                term += bit ? L"x" + to_wstring(j + 1) : L"!x" + to_wstring(j + 1);
            }
            if (!result.empty())
                result += L" | ";
            result += term; // Убрать лишние скобки
        }
    }
    return result.empty() ? L"0" : result;
}

int getPowerOfTwo(size_t n)
{
    if (n == 0)
    {
        return -1;
    }

    int power = 0;
    while (n > 1)
    {
        n >>= 1;
        power++;
    }

    return power;
}

// Сбор конъюнктов для минимизации
void collect_conjunct(const term *t, Conjunct &current)
{
    if (const auto and_term = dynamic_cast<const termAND *>(t))
    {
        collect_conjunct(and_term->t1, current);
        collect_conjunct(and_term->t2, current);
    }
    else if (const auto var = dynamic_cast<const termVAR *>(t))
    {
        current.emplace(var->varname, true);
    }
    else if (const auto not_term = dynamic_cast<const termNOT *>(t))
    {
        if (const auto var = dynamic_cast<const termVAR *>(not_term->t1))
        {
            current.emplace(var->varname, false);
        }
    }
}

vector<Conjunct> collect_conjuncts(const term *t)
{
    vector<Conjunct> clauses;
    if (const auto or_term = dynamic_cast<const termOR *>(t))
    {
        auto left = collect_conjuncts(or_term->t1);
        auto right = collect_conjuncts(or_term->t2);
        clauses.insert(clauses.end(), left.begin(), left.end());
        clauses.insert(clauses.end(), right.begin(), right.end());
    }
    else
    {
        Conjunct c;
        collect_conjunct(t, c);
        if (!c.empty())
            clauses.push_back(c);
    }
    return clauses;
}

// Построение терма через парсинг
term *build_term(const vector<Conjunct> &conjuncts)
{
    if (conjuncts.empty())
        return nullptr;

    // Обработка случая "1"
    if (conjuncts.size() == 1 && conjuncts[0].empty())
    {
        // out << "Popali v slucvai 1" << endl;
        wstring str = L"1";
        wchar_t *cstr = str.data();
        return BoolApp::parsing(cstr);
    }
    wstringstream expr;
    for (size_t i = 0; i < conjuncts.size(); ++i)
    {
        Conjunct c = conjuncts[i];
        wstring term_str;
        for (const auto &lit : c)
        {
            if (!term_str.empty())
                term_str += L"&";
            term_str += lit.second ? lit.first : L"!" + lit.first;
        }
        if (i > 0)
            expr << L"|";
        expr << term_str; // Без скобок
    }

    wstring expr_str = expr.str();
    // out << L"Parsing expression: " << expr_str << endl; // Отладка

    vector<wchar_t> buffer(expr_str.begin(), expr_str.end());
    buffer.push_back(L'\0');
    wchar_t *cstr = buffer.data();
    return BoolApp::parsing(cstr);
}

// Разбиваем строку СДНФ на конъюнкты вручную
vector<Conjunct> parse_conjuncts_from_string(const wstring &expr)
{
    vector<Conjunct> conjuncts;
    wstringstream ss(expr);
    wstring token;

    // Разделяем по '|'
    while (getline(ss, token, L'|'))
    {
        Conjunct c;
        wstringstream ss_term(token);
        wstring lit;

        // Разделяем по '&'
        while (getline(ss_term, lit, L'&'))
        {
            // Удаляем пробелы и скобки
            lit.erase(remove_if(lit.begin(), lit.end(),
                                [](wchar_t ch)
                                { return ch == L' ' || ch == L'(' || ch == L')'; }),
                      lit.end());

            // Обработка отрицаний
            bool is_neg = (lit.find(L'!') == 0);
            wstring var = is_neg ? lit.substr(1) : lit;
            c.emplace(var, !is_neg);
        }

        if (!c.empty())
        {
            conjuncts.push_back(c);
        }
    }

    return conjuncts;
}

// Функция для проверки, можно ли склеить два конъюнкта
bool can_merge(const Conjunct &a, const Conjunct &b, Conjunct &merged)
{
    vector<Literal> diff;
    set_symmetric_difference(
        a.begin(), a.end(),
        b.begin(), b.end(),
        std::back_inserter(diff));

    if (diff.size() != 2)
        return false;
    if (diff[0].first != diff[1].first)
        return false;

    merged = a;
    merged.erase(diff[0]);
    return true;
}

// Алгоритм Квайна-МакКласки (упрощённая версия)
vector<Conjunct> quine_minimization(const vector<Conjunct> &terms)
{
    vector<Conjunct> prime;
    vector<bool> used(terms.size(), false);

    // Поиск склеивающихся термов
    for (size_t i = 0; i < terms.size(); ++i)
    {
        for (size_t j = i + 1; j < terms.size(); ++j)
        {
            Conjunct merged;
            if (can_merge(terms[i], terms[j], merged))
            {
                prime.push_back(merged);
                used[i] = used[j] = true;
            }
        }
        if (!used[i])
            prime.push_back(terms[i]);
    }

    // Удаление дубликатов
    sort(prime.begin(), prime.end());
    prime.erase(unique(prime.begin(), prime.end()), prime.end());

    // Рекурсия, если были изменения
    if (prime.size() != terms.size())
    {
        return quine_minimization(prime);
    }
    return prime;
}

// Проверка, является ли ДНФ тавтологией (покрывает все 2^n комбинаций)
bool is_tautology(const vector<Conjunct> &minimized, int var_count)
{
    return minimized.size() == (1 << var_count); // 2^var_count
}

// Обновлённая функция минимизации
vector<Conjunct> minimize_dnf(const vector<Conjunct> &conjuncts, int var_count)
{
    auto minimized = quine_minimization(conjuncts);

    if (is_tautology(minimized, var_count))
    {
        return {Conjunct()}; // Пустой конъюнкт = 1
    }

    return minimized;
}

wstringstream main(wstringstream in)
{
    wstringstream out;
    uniform_int_distribution<> dis(2, 4);
    int amt_x = dis(gen);
    // auto vf =
    //  Для отладки
    out << L"Enter a vector of function, or enter 'Generate' if you want to generate vector randomly" << endl;
    wstring input;
    in >> input;
    vector<bool> vf;
    if (input == L"Generate")
    {
        vf = generate_vf(amt_x);
    }
    else
    {
        amt_x = getPowerOfTwo(input.size());
        for (auto el : input)
        {
            vf.push_back(el - 48);
        }
    }

    wstring dnf_str = perfect_dnf(amt_x, vf);
    out << L"Generated SDNF: " << dnf_str << endl;

    // Парсим конъюнкты из строки вручную
    auto conjuncts = parse_conjuncts_from_string(dnf_str);
    // out << L"Collected " << conjuncts.size() << L" terms\n"; // 3

    // Минимизируем
    auto minimized = minimize_dnf(conjuncts, amt_x);
    // out << L"After minimization: " << minimized.size() << L" terms\n"; // 2

    // Собираем результат
    term *simplified = build_term(minimized);

    out << L"After minimization: " << simplified->to_string() << endl;

    return out;
}
