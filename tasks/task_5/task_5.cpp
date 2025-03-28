#include "task_5.h"
namespace task5
{
    using namespace std;

    int twoInPower(int power)
    {
        return 1 << power;
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

    vector<bool> makeVecFromOstat(wstring ost1, wstring ost2, int x_num)
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
                res[i + j] = ost1[i_ost] - L'0';
                i_ost++;
            }
        }
        i_ost = 0;
        for (int i = start_pos; i < sz; i += step)
        {
            for (int j = 0; j < start_pos; j++)
            {
                res[i + j] = ost2[i_ost] - L'0';
                i_ost++;
            }
        }

        return res;
    }

    bool has_dum_val(vector<bool> &vf)
    {
        int amt_x = getPowerOfTwo(vf.size());

        if (amt_x == 1)
        {
            return false;
        }

        for (int num_x = 1; num_x <= amt_x; num_x++) // Для каждой переменной проверяем её фиктивность
        {
            bool is_not_dum = false;
            int group_amt = twoInPower(num_x - 1); // группы из 0, которые идут подряд (например 00 и 00, или 0, 0, 0 ,0)
            // Объяснение формулы: длина вектора (2^amt_x) / 2^(amt_x - num_x + 1) = 2^(amt - amt + num - 1)
            // При делении одинаковых оснований степени вычитаются
            int step = twoInPower(amt_x - num_x);
            for (int i = 0; i < group_amt; i += step * 2)
            {
                for (int j = i + step; j < i + step * 2; j++)
                {
                    if (vf[i] != vf[j])
                    {
                        is_not_dum = true;
                        break;
                    }
                }
                if (is_not_dum)
                    break;
            }
            if (!is_not_dum)
            {
                return false;
            }
        }

        return true;
    }

    wstring main(wstring in_str)
    {
        wstringstream in(in_str);
        wstringstream out;
        random_device rd;
        auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
        mt19937 gen(seed);

        uniform_int_distribution<> dis_x(2, 3); // количество переменных
        int amt_x = dis_x(gen);

        // Для отладки
        /*out << "Enter amt_x: ";
        in >> amt_x;
        out << "Amt of vars: " << amt_x << endl;*/

        uniform_int_distribution<> dis_of_dum(0, amt_x); // количество фиктивных переменных
        int amt_dum = dis_of_dum(gen);

        // Для отладки
        /*out << "Enter amt_dum: ";
        in >> amt_dum;
        out << "Amt of dum vars: " << amt_dum << endl;*/

        uniform_int_distribution<> num_of_x(1, amt_x); // рандомайзер для номера переменной
        uniform_int_distribution<> z_or_o(0, 1);       // рандомайзер для 0 и 1

        // Так как это часто используется, заведём переменную
        int two_in_pow_sig_x = twoInPower(amt_x - amt_dum);

        vector<bool> vf_sig(two_in_pow_sig_x); // Буферный вектор переменной только с существенными переменными
        vector<bool> vf;                       // Полный, итоговый вектор переменной

        vector<bool> vars(amt_x + 1); // вектор, фиксирующий фиктивность переменной (1 индексация)

        // раставляем фиктивность переменных
        for (int i = 0; i < amt_dum; i++)
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
        }

        // Для отладки
        /*out << "Enter significant or dum val is:\n";
        for (int i = 1; i < vars.size(); i++)
        {
            out << i << ": ";
            bool t;
            in >> t;
            vars[i] = t;
        }*/

        // рандомайзер номера имени функции
        uniform_int_distribution<> name_of_fun(1, twoInPower(two_in_pow_sig_x) - 2);
        int check = twoInPower(two_in_pow_sig_x);
        do
        {
            int num_name_f = name_of_fun(gen);
            // Для отладки
            /*out << "Enter num of fun: ";
            in >> num_name_f;

            out << "Num_name_f = " << num_name_f << endl;*/

            // Создали вектор использующий все существ переменые
            for (int i = two_in_pow_sig_x - 1; i >= 0; --i)
            {
                // Сдвигаем биты вправо и проверяем значение текущего бита
                bool bit = (num_name_f >> i) & 1;
                vf_sig[(i + two_in_pow_sig_x) % two_in_pow_sig_x] = bit;
            }
        } while (has_dum_val(vf_sig));

        /*for (auto el : vf_sig)
        {
            out << el << ' ';
        }*/
        out << endl;
        int t_amt_x = amt_x - amt_dum; // Текущее количество переменных (количество существенных)
        // Расширяем вектор фиктивными переменными
        vf = vf_sig;
        for (int num_x = 1; num_x < vars.size(); num_x++)
        {
            if (!vars[num_x])
                continue; // проверка на фиктивность переменной
            // out << "For 1: num_x = " << num_x << endl;
            t_amt_x++;
            int group_amt = twoInPower(num_x - 1); // группы из 0, которые идут подряд (например 00 и 00, или 0, 0, 0 ,0)
            // Объяснение формулы: длина вектора (2^amt_x) / 2^(amt_x - num_x + 1) = 2^(amt - amt + num - 1)
            // При делении одинаковых оснований степени вычитаются
            int step = twoInPower(t_amt_x - num_x);
            int index_in_vf = 0;

            vector<bool> buf(twoInPower(t_amt_x));
            for (int i = 0; i < buf.size(); i += step * 2)
            {

                for (int j = i + step, m = i; j < i + step * 2; j++, m++)
                {
                    buf[j] = vf[index_in_vf];
                    buf[m] = vf[index_in_vf];
                    index_in_vf++;
                }
            }
            vf = buf;
        }
        // out << "Determine from the function vector which variables are dummy and significant:\n";
        // out << "Vector of function: (";
        for (auto el : vf)
        {
            out << el;
        }
        out << L' ';
        for (int i = 1; i < vars.size(); i++)
        {
            vars[i] = !vars[i];
            out << vars[i];
        }
        // out << ")" << endl;

        // out << "Enter '1' if dum and '0' if significant\n";
        /*vector<bool> ans_vars(vars.size());
        for (int i = 1; i < ans_vars.size(); i++)
        {
            out << "x" << i << ": ";
            bool t;
            in >> t;
            ans_vars[i] = t;
        }

        for (int i = 1; i < ans_vars.size(); i++)
        {
            if (ans_vars[i] != vars[i])
            {
                out << "Wrong answer! Game over.";
                wstring res;
                res = out.str();
                return res;
            }
        }*/

        // out << "You're right! Game over.";
        wstring res;
        res = out.str();
        return res;
    }
}