#include "task_6.h"
namespace task6
{
    using namespace BoolApp;

    using namespace std;

    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    bool is_literal(term *t)
    {
        if (!t)
            return false;
        if (dynamic_cast<termVAR *>(t))
        {
            return true;
        }
        else if (auto not_term = dynamic_cast<termNOT *>(t))
        {
            return not_term->t1 && dynamic_cast<termVAR *>(not_term->t1);
        }
        return false;
    }

    bool is_dnf(term *t)
    {
        if (!t)
            return false;

        if (dynamic_cast<termEQUAL *>(t))
        {
            return false;
        }
        else if (auto or_term = dynamic_cast<termOR *>(t))
        {
            return is_dnf(or_term->t1) && is_dnf(or_term->t2);
        }
        else if (auto and_term = dynamic_cast<termAND *>(t))
        {
            return is_and_child_dnf(and_term->t1) && is_and_child_dnf(and_term->t2);
        }
        else if (auto not_term = dynamic_cast<termNOT *>(t))
        {
            return is_literal(not_term->t1);
        }
        else if (dynamic_cast<termVAR *>(t))
        {
            return true;
        }
        return false;
    }

    bool is_and_child_dnf(term *t)
    {
        if (auto and_term = dynamic_cast<termAND *>(t))
        {
            return is_dnf(and_term);
        }
        return is_literal(t);
    }

    vector<bool> generate_vf(int n)
    {
        long long k = 1LL << n;
        vector<bool> f(k); // 2^n

        uniform_int_distribution<> dis(0, 1); // Равномерное распределение для 0 и 1

        for (int i = 0; i < k; i++)
        {
            f[i] = dis(gen);
        }

        return f;
    }

    wstring main(wstring in_str)
    {
        wstringstream in(in_str);
        wstringstream out;
        uniform_int_distribution<> dis(1, 4);
        int amt_x = dis(gen);

        vector<bool> v = generate_vf(amt_x); // Система предлагает вектор функции

        // out << L"Enter a DNF, that would be suitable for this vector: (";

        for (auto el : v)
        {
            out << el;
        }
        // out << L")" << endl;
        out << L" ";
        wstring str;
        getline(in, str);
        wchar_t *ch = str.data();
        BoolApp::term *t = BoolApp::parsing(ch);

        // Проверка на ДНФ
        if (!t)
        {
            out << L"Invalid expression." << endl;
            wstring res2;
            res2 = out.str();
            return res2;
        }

        if (!is_dnf(t))
        {
            out << L"Wrong answer. Not a DNF." << endl;
            wstring res2;
            res2 = out.str();
            return res2;
        }

        BoolApp::termData td;
        std::set<std::wstring> st;
        t->get_name_list(st);

        st.erase(wstring(L"0"));
        st.erase(wstring(L"1"));

        /*for (auto el : st)
        {
            out << el << endl;
        }*/

        vector<pair<bool, wstring>> vf;
        for (auto el : st)
        {
            vf.push_back(pair<bool, wstring>{0, el});
        }
        BoolApp::termData data;
        vector<bool> res;

        for (int i = 0; i < (1 << vf.size()); i++)
        {
            for (int j = 0; j < vf.size(); j++)
            {
                data.nametovar[vf[j].second] = i & (1 << j);
            }
            res.push_back(t->calculate(data));
        }
        out << endl;
        if (res.size() != v.size())
        {
            out << L"0" << endl; // Неправильный ответ
            wstring res2;
            res2 = out.str();
            return res2;
        }

        /*for (auto el : res)
        {
            out << el;
        }
        out << endl;*/

        for (int i = 0; i < v.size(); i++)
        {
            if (res[i] != v[i])
            {
                out << L"0" << endl; // Неправильный ответ
                wstring res2;
                res2 = out.str();
                return res2;
            }
        }

        out << L"1" << endl; // Правильный ответ
        wstring res2;
        res2 = out.str();
        return res2;
    }
}