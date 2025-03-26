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

    // Так как это часто используется, заведём переменную
    int two_in_pow_sig_x = twoInPower(amt_x - amt_dum);

    uniform_int_distribution<> name_of_fun(1, two_in_pow_sig_x - 2); // рандомайзер номера имени функции
    int num_name_f = name_of_fun(gen);

    vector<bool> vf_buf(two_in_pow_sig_x); // Буферный вектор переменной только с существенными переменными
    vector<bool> vf(twoInPower(amt_x));    // Полный, итоговый вектор переменной

    vector<bool> vars(amt_x + 1); // вектор, фиксирующий фиктивность переменной (1 индексация)
    // vars[0] = 1;
    vars[2] = 1;
    vars[4] = 1;
    // раставляем фиктивность переменных
    /*for (int i = 0; i < amt_dum; i++)
    {
        while (true)
        {
            int ind_of_dum = num_of_x(gen);
            if (!vars[ind_of_dum])
            {
                vars[ind_of_dum] = 1;
                break;
            }
        }
    }*/

    // Создали вектор использующий все существ переменые

    for (int i = two_in_pow_sig_x - 1; i >= 0; --i)
    {
        // Сдвигаем биты вправо и проверяем значение текущего бита
        int bit = (num_name_f >> i) & 1;
        vf_buf[(i + two_in_pow_sig_x) % two_in_pow_sig_x] = bit;
    }

    cout << "Vector buffer:\n";
    for (auto el : vf_buf)
    {
        cout << el << ' ';
    }
    cout << endl;

    // расширим вектор фиктивными переменными

    int t_amt_x = amt_x - amt_dum + 1; // Относительное общее число переменных
    for (int k = 0; k < amt_dum; k++, t_amt_x++)
    {
        int num_dum_x = 1;
        while (num_dum_x < vars.size())
        {
            if (vars[num_dum_x])
            {
                vars[num_dum_x] = 0;
                break;
            }
            num_dum_x++;
        }
        // Для отладки:
        cout << "Num_dum_x = " << num_dum_x << endl;
        //

        int step = twoInPower(t_amt_x - num_dum_x);
        int ind_in_buf = 0;
        // int counter = 0; // счётчик переходов для ind_in_buf
        for (int i = 0; i < twoInPower(t_amt_x); i += step * 2)
        {
            for (int j = i; j < i + step; j++)
            {
                vf[j] = vf_buf[ind_in_buf];
                vf[j + step] = vf[ind_in_buf];
                cout << "j = " << j << "  ";
                cout << "ind_in_buf = " << ind_in_buf << '\n';
                cout << "j + step = " << j + step << "  ";
                cout << "ind_in_buf = " << ind_in_buf << '\n';
                ind_in_buf++;
                /*counter++;
                if (counter >= 2)
                {
                    ind_in_buf++;
                    counter = 0;
                }*/
            }
        }
        vf_buf = vf;
        cout << "Result vector:\n";
        for (auto el : vf)
        {
            cout << el << ' ';
        }
        cout << endl;
    }

    /*cout << "Result vector:\n";
    for (auto el : vf)
    {
        cout << el << ' ';
    }
    cout << endl;*/
}