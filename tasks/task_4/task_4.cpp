#include "task_4.h"

namespace task4
{
    using namespace std;

    wstring main(wstring in_str)
    {
        wstringstream in(in_str);
        wstringstream out;
        random_device rd;
        auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();

        mt19937 gen(seed);
        uniform_int_distribution<> dis(0, 15);

        int num = dis(gen);

        // out << L"Guess the name of the function by its vector. Name from 1 to 16.\nYou have three attempts\n";
        // out << L"\nVector of function: (";

        vector<bool> vf(4);
        for (int i = 3; i >= 0; --i)
        {
            // Сдвигаем биты вправо и проверяем значение текущего бита
            int bit = (num >> i) & 1;
            vf[(i + 4) % 4] = bit;
        }
        for (auto el : vf)
        {
            out << el;
        }
        wstring name;

        switch (num)
        {
        case 0:
            name = L"Нулевая";
        case 1:
            name = L"Конъюнкция";
        case 2:
            name = L"Обратная импликация";
        case 3:
            name = L"Переменная 1";
        case 4:
            name = L"Обратная коимпликация";
        case 5:
            name = L"Переменная 2";
        case 6:
            name = L"Сложение";
        case 7:
            name = L"Дизъюнкция";
        case 8:
            name = L"Стрелка Пирса";
        case 9:
            name = L"Эквивалентность";
        case 10:
            name = L"Отрицание переменной 2";
        case 11:
            name = L"Коимпликация";
        case 12:
            name = L"Отрицание переменной 1";
        case 13:
            name = L"Импликация";
        case 14:
            name = L"Штрих Шеффера";
        case 15:
            name = L"Единичная";
        }

        out << name;
        /*out << L')' << endl;
        int i = 0;
        int ans;
        out << L"\nEnter the function name:\n";
        while (i < 3)
        {
            in >> ans;
            i++;
            if (ans != num + 1)
            {
                out << L"Incorrect.\n";
            }
            else
            {
                out << L"That's right! Well done, take a pie from the shelf!";
                break;
            }
        }
        out << L"Game over";*/

        wstring res;
        res = out.str();
        return res;
    }
}