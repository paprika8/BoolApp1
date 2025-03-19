#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>
#include <utility>

using namespace std;

int twoInPower(int power)
{
    if (power == 0)
        return 1;

    int res = 2;
    while (power > 1)
    {
        res <<= 1;
        power--;
    }
    return res;
}

vector<bool> makeVecFromOstat(string ost1, string ost2, int x_num)
{
    int sz = ost1.size() + ost2.size();
    int group_amt = twoInPower(x_num - 1);
    int step = sz / group_amt;
    int start_pos = sz / twoInPower(x_num);

    vector<bool> res(sz);
    int i_ost = 0;

    for (int i = 0; i < sz; i += step)
    {
        for (int j = 0; j < start_pos; j++)
        {
            res[i + j] = ost1[i_ost] - 48;
            i_ost++;
        }
    }
    i_ost = 0;
    for (int i = start_pos; i < sz; i += step)
    {
        for (int j = 0; j < start_pos; j++)
        {
            res[i + j] = ost2[i_ost] - 48;
            i_ost++;
        }
    }

    return res;
}

int main()
{
    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    uniform_int_distribution<> dis_x(2, 3); // количество переменных
    int amt_x = dis_x(gen);
    cout << "Amt of vars: " << amt_x << endl;
    uniform_int_distribution<> dis_of_dum(0, amt_x); // количество фиктивных переменных
    int amt_dum = dis_of_dum(gen);
    cout << "Amt of dum vars: " << amt_dum << endl;
    uniform_int_distribution<> num_of_x(1, amt_x); // рандомайзер для номера переменной
    uniform_int_distribution<> z_or_o(0, 1);       // рандомайзер для 0 и 1

    vector<pair<bool, bool>> vars(amt_x + 1, pair(0, 1)); // вектор, фиксирующий фиктивность переменной
    vars[0].first = 1;
    vars[0].second = 0;
    // раставляем фиктивность переменных
    for (int i = 0; i < amt_dum; i++)
    {
        while (true)
        {
            int ind_of_dum = num_of_x(gen);
            if (!vars[ind_of_dum].first)
            {
                vars[ind_of_dum].first = 1;
                break;
            }
        }
    }
    // Работаем с существенными переменными
    vector<pair<bool, bool>> vars_for_ans = vars;

    int num_signif_x = vars.size() - 1;
    while (num_signif_x > 0)
    {
        if (!vars[num_signif_x].first && vars[num_signif_x].second)
        {
            vars[num_signif_x].second = 0;
            break;
        }
        num_signif_x--;
    }
    if (num_signif_x <= 0)
    {
        for (int i = 0; i < twoInPower(amt_x); i++)
        {
            cout << '0';
        }
        cout << endl;
        return 0;
    }

    vars = vars_for_ans;
    // int len_ost_vec = twoInPower(amt_x - num_signif_x);
    int len_ost_vec = twoInPower(amt_x - 1);
    string ost1 = "";
    for (int j = 0; j < len_ost_vec; j++)
    {
        ost1 += '0';
    }
    string ost2 = "";
    for (int j = 0; j < len_ost_vec; j++)
    {
        ost2 += '1';
    }

    vector<bool> v = makeVecFromOstat(ost1, ost2, num_signif_x);
    cout << "num_signif_x = " << num_signif_x << endl;
    cout << "v size = " << v.size() << endl;

    for (int j = 0; j < v.size(); j++)
    {
        cout << v[j] << ' ';
    }
    cout << endl;
    num_signif_x--;
    for (int i = 0; i < amt_x - amt_dum; i++)
    {
        // тут работаем с остальными существенными переменными
        while (num_signif_x >= 0)
        {
            if (!vars[num_signif_x].first && vars[num_signif_x].second)
            {
                vars[num_signif_x].second = 0;
                break;
            }
            num_signif_x--;
        }
        if (num_signif_x < 0)
        {
            break;
        }
        cout << "num_signif = " << num_signif_x << endl;

        // Инвертируем случайное количество бит, на случайных местах
        int start_pos = twoInPower(amt_x - num_signif_x);
        uniform_int_distribution<> ind_x(0, v.size() - 1);
        int pos = ind_x(gen);
        cout << "pos = " << pos << endl;
        v[pos] = !(v[pos]);
        for (int j = 0; j < v.size(); j++)
        {
            cout << v[j] << ' ';
        }
        cout << endl;
    }

    // Обработаем вектор так, чтобы фиктивные остались фиктивными
    for (int i = 0; i < amt_dum; i++)
    {
        int num_dum_x = amt_x;
        while (num_dum_x > 0)
        {
            if (vars[num_dum_x].first)
            {
                vars[num_dum_x].first = 0;
                break;
            }
            num_dum_x--;
        }
        cout << "num_dum_x = "
             << num_dum_x << "\n\n";

        int step = twoInPower(num_dum_x);
        int k = 0;
        // Проверь шаг, что то с ним не так, придётся пересчитать
        for (int i = 0; i < v.size(); i += step * 2)
        {
            cout << "Enter the cycle\n";
            k = i;
            for (int j = i + step * 2; j < v.size(); j++, k++)
            {
                cout << "Enter the second cycle\n";
                v[k] = v[j];
                cout << "k = " << k << "; j = " << j << endl;
            }
        }
    }

    // Описание алгоритма создания вектора:
    // Идём от самых "дальних" фиктивных переменных, то есть от переменных с самым большим индексом
    // И составляем для их 0 и 1 остаточных одинаковые векторы (чтобы они были фиктивными)
    // Затем для последующих переменных копируем этот вектор, чтобы у них на 0 и 1 остаточных тоже были
    // одинаковые значения
    // механизм составления вектора понятен
    // и механизм соединения двух остточных по номеру переменной в вектор уже готов (задание 3)

    // Переработанный алгоритм:
    // Идём от дальних существенных переменных.
    // Делаем для них тоже самое,  нам нужно просто сформировать какой то вектор функции
    // Так же для всех последующих нужно чуть чуть менять, но не так, чтобы прошлые становились фиктивными

    for (auto el : v)
    {
        cout << el << ' ';
    }
}