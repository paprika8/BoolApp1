#include "..\..\terms\term.hpp"
#include <iostream>
#include <time.h>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

random_device rd;
auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
mt19937 gen(seed);

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

bool is_in_T0(vector<bool> &vf)
{
    return !vf[0];
}

bool is_in_T1(vector<bool> &vf)
{
    return vf[vf.size() - 1];
}

bool is_in_S(vector<bool> &vf)
{
    auto l = vf.begin();
    auto r = vf.end() - 1;
    for (int i = 0; i < vf.size() / 2; i++, l++, r--)
    {
        if (*l == *r)
        {
            return false;
        }
    }
    return true;
}

bool is_in_M(vector<bool> &vf)
{
    int amt_x = getPowerOfTwo(vf.size());
    vector<int> compar_group(vf.size());

    for (int i = 0; i < vf.size(); i++)
    {
        int cnt = 0;
        for (int j = 1; j <= amt_x; j++)
        {
            if (((i >> amt_x - j) & 1)) // если один
            {
                cnt++;
            }
        }
        compar_group[i] = cnt;
    }

    for (int i = 0; i < vf.size() - 1; i++)
    {
        for (int j = i + 1; j < vf.size(); j++)
        {
            if (compar_group[i] < compar_group[j] && vf[j] < vf[i])
            {
                return false;
            }
        }
    }
    return true;
}

bool is_in_L(vector<bool> &vf)
{
    int amt_x = getPowerOfTwo(vf.size());
    vector<bool> buf = vf;
    for (int i = 1; i < buf.size(); i++)
    {
        for (int j = i; j < buf.size(); j++)
        {
            buf[j] = (!buf[j - 1] && buf[j] || buf[j - 1] && !buf[j]); // Сложение по модулю два
            if (buf[j] && j == i)
            {
                int cnt = 0;
                for (int k = 1; k <= amt_x; k++) // смотрим на количество
                {
                    if (((i >> amt_x - k) & 1)) // если один
                    {
                        cnt++;
                    }
                }
                if (cnt > 1)
                {
                    return false;
                }
            }
        }
    }

    return true;
}

int main()
{
    uniform_int_distribution<> dis(1, 4);
    int amt_x = dis(gen);

    vector<bool> vf = generate_vf(amt_x); // Система предлагает вектор функции

    cout << "Vector of function: (";
    for (auto el : vf)
    {
        cout << el;
    }
    cout << ")\n";

    // T0, T1, S, M, L - классы
    //  0,  1, 2, 3, 4 - индексы
    vector<bool> f_types(5, 0);

    int types_cnt = 0;

    if (is_in_T0(vf))
    {
        f_types[0] = true;
        types_cnt++;
    }
    if (is_in_T1(vf))
    {
        f_types[1] = true;
        types_cnt++;
    }
    if (is_in_S(vf))
    {
        f_types[2] = true;
        types_cnt++;
    }
    if (is_in_M(vf))
    {
        f_types[3] = true;
        types_cnt++;
    }
    if (is_in_L(vf))
    {
        f_types[4] = true;
        types_cnt++;
    }

    vector<bool> answers(5, 0);
    int ans_cnt = 0;

    cout << "Enter in which semi-full classes the vector of function is included (T0, T1, S, M, L).\nOne class at a time" << endl;
    int miss_cnt = 0;
    while (miss_cnt < 3)
    {
        if (ans_cnt == types_cnt)
        {
            cout << "Good job! That's all.\nGame over.";
            return 0;
        }
        string input;
        cin >> input;
        if (input != "S" && input != "M" && input != "L" && input != "T1" && input != "T0")
        {
            cout << "Wrong input. You can enter only T0, T1, S, M, L.\nTry again." << endl;
            continue;
        }

        if (input == "T0" && f_types[0] && !answers[0])
        {
            cout << "Well done!" << endl;
            answers[0] = true;
            ans_cnt++;
            continue;
        }
        if (input == "T1" && f_types[1] && !answers[1])
        {
            cout << "Well done!" << endl;
            answers[1] = true;
            ans_cnt++;
            continue;
        }
        if (input == "S" && f_types[2] && !answers[2])
        {
            cout << "Well done!" << endl;
            answers[2] = true;
            ans_cnt++;
            continue;
        }
        if (input == "M" && f_types[3] && !answers[3])
        {
            cout << "Well done!" << endl;
            answers[3] = true;
            ans_cnt++;
            continue;
        }
        if (input == "L" && f_types[4] && !answers[4])
        {
            cout << "Well done!" << endl;
            answers[4] = true;
            ans_cnt++;
            continue;
        }

        if (input == "T0" && answers[0])
        {
            cout << "Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
            continue;
        }
        if (input == "T1" && answers[1])
        {
            cout << "Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
            continue;
        }
        if (input == "S" && answers[2])
        {
            cout << "Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
            continue;
        }
        if (input == "M" && answers[3])
        {
            cout << "Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
            continue;
        }
        if (input == "L" && answers[4])
        {
            cout << "Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
            continue;
        }

        miss_cnt++;
        if (miss_cnt >= 3)
        {
            cout << "Wrong answer. You lose.\nGame over." << endl;
            return 0;
        }
        cout << "Wrong answer, you have " << 3 - miss_cnt << " attemps.\nTry again." << endl;
    }
}