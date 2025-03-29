#include "task_6.h"
namespace task6
{
    using namespace BoolApp;

    using namespace std;

    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    bool is_literal(term *t)
    {
        if (!t)
            return false;
        if (dynamic_cast<termVAR *>(t))
        {
            return true;
        }
        else if (auto not_term = dynamic_cast<termNOT *>(t))
        {
            return not_term->t1 && dynamic_cast<termVAR *>(not_term->t1);
        }
        return false;
    }
    bool is_and(term *t){
        if (!t)
            return false;
        if (auto and_term = dynamic_cast<termAND *>(t))
        {
            return is_literal(and_term->t1) && is_and(and_term->t2);
        }
        return is_literal(t);
    }

    bool is_dnf(term *t)
    {
        if (!t)
            return false;

        if (dynamic_cast<termEQUAL *>(t))
        {
            return false;
        }
        else if (auto or_term = dynamic_cast<termOR *>(t))
        {
            return is_and(or_term->t1) && is_dnf(or_term->t2);
        }
        else if (auto and_term = dynamic_cast<termAND *>(t))
        {
            return is_and(t);
        }

        return is_literal(t);
    }

    /*bool is_and_child_dnf(term *t)
    {
        if (auto and_term = dynamic_cast<termAND *>(t))
        {
            return is_dnf(and_term);
        }
        return is_literal(t);
    }*/

    vector<bool> generate_vf()
    {
        uniform_int_distribution<> dis(2, 4);
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

    wstring main(wstring in_str, const std::vector<bool> &v)
    {
        std::wstringstream in(in_str);
        std::wstringstream out;
        /*uniform_int_distribution<> dis(1, 4);
        int amt_x = dis(gen);*/

        // vector<bool> v = generate_vf(amt_x); // Система предлагает вектор функции

        // out << L"Enter a DNF, that would be suitable for this vector: (";

        /*for (auto el : v)
        {
            out << el;
        }
        // out << L")" << endl;
        out << L" ";
        */
        std::wstring str;
        getline(in, str);
        int n_arg = -1;
        {
            int a = v.size();
            while(a){
                ++n_arg;
                a/=2;
            }
        }
        wchar_t *ch = str.data();
        BoolApp::term *t = BoolApp::parsing(ch);

        // Проверка на ДНФ
        if (!t)
        {
            out << L"2"; // L"Invalid expression." << endl;
            wstring res2;
            res2 = out.str();
            return res2;
        }

        if (!t->correct() || !is_dnf(t))
        {
            out << L"3"; // L"Wrong answer. Not a DNF." << endl;
            wstring res2;
            res2 = out.str();
            return res2;
        }

        BoolApp::termData td;
        std::set<std::wstring> st;
        t->get_name_list(st);

        st.erase(wstring(L"0"));
        st.erase(wstring(L"1"));

        for(int i = 1; i <= n_arg; i++){
            st.insert(wstring(L"x") + to_wstring(i));
        }

        /*for (auto el : st)
        {
            out << el << endl;
        }*/

        std::vector<std::pair<bool, std::wstring>> vf;
        for (auto el : st)
        {
            vf.push_back(pair<bool, wstring>{0, el});
        }
        BoolApp::termData data;
        std::vector<bool> res;

        for (int i = 0; i < (1 << vf.size()); i++)
        {
            for (int j = 0; j < vf.size(); j++)
            {
                data.nametovar[vf[vf.size() - j - 1].second] = i & (1 << j);
            }
            res.push_back(t->calculate(data));
        }
        //out << endl;
        if (res.size() != v.size())
        {
            out << L"0";// << endl; // Неправильный ответ
            std::wstring res2;
            res2 = out.str();
            return res2;
        }

        /*for (auto el : res)
        {
            out << el;
        }
        out << endl;*/

        for (int i = 0; i < v.size(); i++)
        {
            if (res[i] != v[i])
            {
                out << L"0";// << endl; // Неправильный ответ
                std::wstring res2;
                res2 = out.str();
                return res2;
            }
        }

        out << L"1";// << endl; // Правильный ответ
        std::wstring res2;
        res2 = out.str();
        return res2;
    }
}