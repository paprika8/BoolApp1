#include <iostream>
#include <random>
#include <vector>
#include <chrono>

using namespace std;

void log_table(int n, vector<bool> &v)
{
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

            cout << "  " << t << " |";
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

    log_table(n, f);
}