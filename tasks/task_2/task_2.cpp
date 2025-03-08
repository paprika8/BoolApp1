#include "..\..\terms\term.hpp"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

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
//| x1 | x2 | x3 | f |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  0 | 0 |
//|  0 |  0 |  1 | 0 |
//|  0 |  0 |  1 | 0 |
int main()
{
    srand(time(NULL));

    int n;
    cin >> n;
    int m = 1 << n;
    vector<bool> f(m);
    int k = 1 << m;
    int d = rand() % k;

    for (int i = m - 1; i >= 0; i--)
    {
        f[i] = d & 1;
        d >>= 1;
    }
    log_table(n, f);
}