#include "task_10.h"
namespace task10
{
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

    vector<bool> generate_vf()
    {
        uniform_int_distribution<> dis(1, 4);
        int amt_x = dis(gen);
        long long k = 1LL << amt_x;
        vector<bool> f(k); // 2^n

        uniform_int_distribution<> dis2(0, 1); // Равномерное распределение для 0 и 1

        for (int i = 0; i < k; i++)
        {
            f[i] = dis2(gen);
        }

        return f;
    }

    bool is_in_T0(const vector<bool> &vf)
    {
        return !vf[0];
    }

    bool is_in_T1(const vector<bool> &vf)
    {
        return vf[vf.size() - 1];
    }

    bool is_in_S(const vector<bool> &vf)
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

    bool is_in_M(const vector<bool> &vf)
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

    bool is_in_L(const vector<bool> &vf)
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

    vector<bool> main(const vector<bool> &vf)
    {
        // wstringstream in(in_str);
        wstringstream out;

        // vector<bool> vf = generate_vf(); // Система предлагает вектор функции

        // out << L"Vector of function: (";
        /*for (auto el : vf)
        {
            out << el;
        }*/
        // out << L")\n";
        // out << L" ";
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

        for (auto el : f_types)
        {
            out << el;
        }

        /*vector<bool> answers(5, 0);
        int ans_cnt = 0;

        out << L"Enter in which semi-full classes the vector of function is included (T0, T1, S, M, L).\nOne class at a time" << endl;
        int miss_cnt = 0;
        while (miss_cnt < 3)
        {
            if (ans_cnt == types_cnt)
            {
                out << L"1"; // Верный ответ
                wstring res;
                res = out.str();
                return res;
            }
            wstring input;
            in >> input;
            if (input != L"S" && input != L"M" && input != L"L" && input != L"T1" && input != L"T0")
            {
                out << L"Wrong input. You can enter only T0, T1, S, M, L.\nTry again." << endl;
                continue;
            }

            if (input == L"T0" && f_types[0] && !answers[0])
            {
                out << L"Well done!" << endl;
                answers[0] = true;
                ans_cnt++;
                continue;
            }
            if (input == L"T1" && f_types[1] && !answers[1])
            {
                out << L"Well done!" << endl;
                answers[1] = true;
                ans_cnt++;
                continue;
            }
            if (input == L"S" && f_types[2] && !answers[2])
            {
                out << L"Well done!" << endl;
                answers[2] = true;
                ans_cnt++;
                continue;
            }
            if (input == L"M" && f_types[3] && !answers[3])
            {
                out << L"Well done!" << endl;
                answers[3] = true;
                ans_cnt++;
                continue;
            }
            if (input == L"L" && f_types[4] && !answers[4])
            {
                out << L"Well done!" << endl;
                answers[4] = true;
                ans_cnt++;
                continue;
            }

            if (input == L"T0" && answers[0])
            {
                out << L"Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
                continue;
            }
            if (input == L"T1" && answers[1])
            {
                out << L"Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
                continue;
            }
            if (input == L"S" && answers[2])
            {
                out << L"Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
                continue;
            }
            if (input == L"M" && answers[3])
            {
                out << L"Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
                continue;
            }
            if (input == L"L" && answers[4])
            {
                out << L"Yeah, I know that you know it, but may be anything else?\nTry again." << endl;
                continue;
            }

            miss_cnt++;
            if (miss_cnt >= 3)
            {
                out << L"Wrong answer. You lose.\nGame over." << endl;
                wstring res;
                res = out.str();
                return res;
            }
            out << L"Wrong answer, you have " << 3 - miss_cnt << L" attemps.\nTry again." << endl;
        }*/
        wstring res;
        res = out.str();
        return f_types;
    }
}
