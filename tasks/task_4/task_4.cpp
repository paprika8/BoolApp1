#include "task_4.h"

namespace task4
{
    using namespace std;

    wstring get_name(int num){
        wstring name;
        switch (num)
        {
        case 0:
            name = L"Нулевая";
            break;
        case 1:
            name = L"Конъюнкция";
            break;
        case 11:
            name = L"Обратная импликация";
            break;
        case 3:
            name = L"Переменная 1";
            break;
        case 4:
            name = L"Обратная коимпликация";
            break;
        case 5:
            name = L"Переменная 2";
            break;
        case 6:
            name = L"Сложение";
            break;
        case 7:
            name = L"Дизъюнкция";
            break;
        case 8:
            name = L"Стрелка Пирса";
            break;
        case 9:
            name = L"Эквивалентность";
            break;
        case 10:
            name = L"Отрицание переменной 2";
            break;
        case 2:
            name = L"Коимпликация";
            break;
        case 12:
            name = L"Отрицание переменной 1";
            break;
        case 13:
            name = L"Импликация";
            break;
        case 14:
            name = L"Штрих Шеффера";
            break;
        case 15:
            name = L"Единичная";
            break;
        }
        return name;
    }

    wstring main(/*wstring in_str, */wstring& an)
    {
        //wstringstream in(in_str);
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
        /*for (int i = 0; i < 4; ++i)
        {
            // Сдвигаем биты вправо и проверяем значение текущего бита
            int bit = (num >> i) & 1;
            vf[(i + 4) % 4] = bit;
        }*/
        for (int i = 3; i >= 0; --i)
        {
            out << vf[i];
        }
        wstring name = get_name(num);

        an += name;

        //out << name;
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