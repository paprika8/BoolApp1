#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

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

void log_table(vector<bool> &v)
{
    int n = getPowerOfTwo(v.size());

    cout << '|';
    for (int i = 1; i <= n; i++)
    {
        cout << " x" << i << " |";
    }
    cout << " f |" << '\n';
    for (int i = 0; i < v.size(); i++)
    {
        cout << '|';

        for (int j = n - 1; j >= 0; j--)
        {
            int offs = 1 << j;
            bool t = i & offs;

            for (int k = 0; k < countDigits(n - j) + 1; k++)
            {
                cout << ' ';
            }
            cout << t << " |";
        }

        cout << ' ' << v[i] << " |" << '\n';
    }
}
//| x1 | x2 | f |
//|  0 |  0 | 1 |
//|  0 |  1 | 0 |
//|  1 |  0 | 1 |
//|  1 |  1 | 0 |
int main()
{
    int n;
    cin >> n;

    long long k = 1LL << n;
    vector<bool> f(k); // 2^n

    // Инициализация генератора случайных чисел
    random_device rd; // Источник энтропии
    // Используем текущее время как дополнительный источник энтропии
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();

    mt19937 gen(seed);                    // Генератор случайных чисел (Mersenne Twister)
    uniform_int_distribution<> dis(0, 1); // Равномерное распределение для 0 и 1

    for (int i = 0; i < k; i++)
    {
        f[i] = dis(gen);
    }

    log_table(f);
}