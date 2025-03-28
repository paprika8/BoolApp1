#include "task_1.h"

using namespace std;

namespace task1
{
    int countDigits(int number)
    {
        if (number == 0)
        {
            return 1; // Число 0 имеет одну цифру
        }

        int count = 0;
        while (number != 0)
        {
            number /= 10; // Убираем последнюю цифру
            count++;
        }
        return count;
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

    void log_table(vector<bool> &v, wstringstream &out)
    {
        int n = getPowerOfTwo(v.size());

        out << L'|';
        for (int i = 1; i <= n; i++)
        {
            out << L" x" << i << L" |";
        }
        out << L" f |" << L'\n';
        for (int i = 0; i < v.size(); i++)
        {
            out << L'|';

            for (int j = n - 1; j >= 0; j--)
            {
                int offs = 1 << j;
                bool t = i & offs;

                for (int k = 0; k < countDigits(n - j) + 1; k++)
                {
                    out << L' ';
                }
                out << t << L" |";
            }

            out << L' ' << v[i] << L" |" << L'\n';
        }
    }
    //| x1 | x2 | f |
    //|  0 |  0 | 1 |
    //|  0 |  1 | 0 |
    //|  1 |  0 | 1 |
    //|  1 |  1 | 0 |
    wstring main(wstring in_str)
    {
        wstringstream in(in_str);
        wstringstream out;
        int n;
        in >> n;

        long long k = 1LL << n;
        vector<bool> f(k); // 2^n

        // Инициализация генератора случайных чисел
        random_device rd; // Источник энтропии
        // Используем текущее время как дополнительный источник энтропии
        auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();

        mt19937 gen(seed);                    // Генератор случайных чисел
        uniform_int_distribution<> dis(0, 1); // Равномерное распределение для 0 и 1

        for (int i = 0; i < k; i++)
        {
            f[i] = dis(gen);
        }

        // log_table(f, out);
        for (auto el : f)
        {
            out << el;
        }
        wstring res;
        res = out.str();
        return res;
    }
}