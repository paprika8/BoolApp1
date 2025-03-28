#include "task_11.h"
namespace task11
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

    vector<vector<bool>> gen_system_of_vecs()
    {
        vector<vector<bool>> res;
        uniform_int_distribution<> dis_amt_sets(1, 5);
        int amt_vec = dis_amt_sets(gen);
        while (amt_vec--)
        {
            uniform_int_distribution<> dis(1, 4);
            int amt_x = dis(gen);

            vector<bool> vf = generate_vf(amt_x); // Система предлагает вектор функции
            res.push_back(vf);
        }
        return res;
    }

    vector<bool> generate_vf(int n)
    {
        long long k = 1LL << n;
        vector<bool> f(k); // 2^n

        uniform_int_distribution<> dis2(0, 1); // Равномерное распределение для 0 и 1

        for (int i = 0; i < k; i++)
        {
            f[i] = dis2(gen);
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

        for (int i = 0; i < vf.size() - 1; i++)
        {
            for (int j = i + 1; j < vf.size(); j++)
            {
                bool more = 0, less = 0;
                for (int k = 1; k <= amt_x; k++)
                {
                    bool first_bit = ((i >> amt_x - k) & 1);
                    bool second_bit = ((j >> amt_x - k) & 1);

                    if (first_bit < second_bit)
                    {
                        less = true;
                    }
                    if (first_bit > second_bit)
                    {
                        more = true;
                    }
                }
                if (more && less)
                {
                    continue;
                }
                if (less)
                {
                    if (vf[i] > vf[j])
                    {
                        return false;
                    }
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

    wstring main(const vector<vector<bool>> vectors, vector<bool> &classes, bool &full)
    {
        // wstringstream in(in_str);
        wstringstream out;

        // T0, T1, S, M, L - классы
        //  0,  1, 2, 3, 4 - индексы
        vector<bool> f_types(5, 1);

        for (int num_vec = 0; num_vec < vectors.size(); num_vec++)
        {

            uniform_int_distribution<> dis(1, 4);
            int amt_x = dis(gen);

            vector<bool> vf = vectors[num_vec]; // Система предлагает вектор функции

            // Для отладки:
            /*wstring input;
            in >> input;
            vector<bool> vf;
            for (auto el : input)
            {
                vf.push_back(el - 48);
            }*/

            // out << L"Vector of function: (";
            for (auto el : vf)
            {
                int buf = int(el);
                out << buf;
            }
            // out << L")\n";
            out << L" ";

            if (f_types[0] && !is_in_T0(vf))
            {
                f_types[0] = false;
            }
            if (f_types[1] && !is_in_T1(vf))
            {
                f_types[1] = false;
            }
            if (f_types[2] && !is_in_S(vf))
            {
                f_types[2] = false;
            }
            if (f_types[3] && !is_in_M(vf))
            {
                f_types[3] = false;
            }
            if (f_types[4] && !is_in_L(vf))
            {
                f_types[4] = false;
            }
        }

        classes.push_back(f_types[0]);
        classes.push_back(f_types[1]);
        classes.push_back(f_types[2]);
        classes.push_back(f_types[3]);
        classes.push_back(f_types[4]);

        if (!f_types[0] && !f_types[1] && !f_types[2] && !f_types[3] && !f_types[4])
        {
            // out << L"System is complete.\n"; // Система полна
            out << L"1";
            full = 1;
            wstring res;
            res = out.str();
            return res;
        }
        else
        {
            out << L"0 ";
            for (auto el : f_types)
            {
                int buf = int(el);
                out << to_wstring(buf);
            }

            /*bool answered = 0;
            // out << L"System is incomplete.\nEnter the enclosed class which the function is in.\n";
            int miss_cnt = 0;
            while (true)
            {
                if (answered)
                {
                    out << L"Good job! That's all.\nGame over.";
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

                if (input == L"T0" && f_types[0])
                {
                    out << L"Well done!" << endl;
                    answered = true;
                    continue;
                }
                if (input == L"T1" && f_types[1])
                {
                    out << L"Well done!" << endl;
                    answered = true;
                    continue;
                }
                if (input == L"S" && f_types[2])
                {
                    out << L"Well done!" << endl;
                    answered = true;
                    continue;
                }
                if (input == L"M" && f_types[3])
                {
                    out << L"Well done!" << endl;
                    answered = true;
                    continue;
                }
                if (input == L"L" && f_types[4])
                {
                    out << L"Well done!" << endl;
                    answered = true;
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
            }
        }*/
            wstring res;
            res = out.str();
            return res;
        }
    }
}