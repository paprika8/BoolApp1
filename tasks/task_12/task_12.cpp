#include "task_12.h"
namespace task12
{
    using namespace std;
    using namespace BoolApp;

    random_device rd;
    auto seed = rd() ^ chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);

    // Генерация случайного вектора функции
    vector<bool> generate_vf()
    {
        uniform_int_distribution<> dis2(2, 4);
        int n = dis2(gen);
        vector<bool> f(1 << n);
        uniform_int_distribution<> dis(0, 1);
        for (auto b : f)
            b = dis(gen);
        return f;
    }
    vector<bool> generate_vf(int n)
    {
        vector<bool> f(1 << n);
        uniform_int_distribution<> dis(0, 1);
        for (auto b : f)
            b = dis(gen);
        return f;
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

    vector<int> to_vector(int n, int a){
        vector<int> res;
        while(n--){
            res.push_back((a & (1 << n)) >> n);
        }
        return res;
    }
    int v_to_int(vector<int> a){
        int res;
        int n = a.size();
        while(--n){
            if(a[n] != 2)
                res += a[n] << n;
        }
        return res;
    }
    bool equl(vector<int> a, vector<int> b){
        for(int i = 0; i < a.size(); i++){
            if(a[i] != b[i])
                return 0;
        }
        return 1;
    }

    vector<int> compare(vector<int> a, vector<int> b, bool &f){
        int it = -1;
        for(int i = 0; i < a.size(); i++){
            if(a[i] != b[i])
                if(it == -1){
                    it = i;
                }
                else{
                    f = 1;
                    return vector<int>();
                }
        }
        if(it == -1){
            f = 1;
            return vector<int>();
        }
        if(a[it] == 2 || b[it] == 2){
            f = 1;
            return vector<int>();
        }
        vector<int> res(a.size());
        for(int i = 0; i < a.size(); i++)
            if(i == it)
                res[i] = 2;
            else
                res[i] = a[i];
        return res;
    }

    term* create_dnf(const vector<wstring> variables, vector<int> n){
        term* res = 0;
        for(int i = 0; i < n.size(); i++){
            if(n[i] == 1){
                termVAR* v = new termVAR();
                v->varname = variables[i];
                if(!res){
                    res = v;
                }
                else{
                    termAND* and_t = new termAND();
                    and_t->t1 = res;
                    and_t->t2 = v;
                    res = and_t;
                }
            }
            if(n[i] == 0){
                termNOT* t = new termNOT();
                termVAR* v = new termVAR();
                v->varname = variables[i];
                t->t1 = v;
                if(!res){
                    res = t;
                }
                else{
                    termAND* and_t = new termAND();
                    and_t->t1 = res;
                    and_t->t2 = t;
                    res = and_t;
                }
            }
        }
        return res;
    }

    std::wstring vec_to_wstring(vector<int> &vf)
	{
		std::wstring res;
		for (auto el : vf)
		{
			int buf = int(el);
			res += std::to_wstring(buf);
		}
		return res;
	}

    wstring getAns(vector<bool> vf){
        int n_arg = -1;
        {
            int a = vf.size();
            while(a){
                ++n_arg;
                a/=2;
            }
        }
        int b = 0;
        map<int, bool> bins;
        map<int, vector<int>> minimaze;
        int flag_null = 1;
        for(;b < vf.size(); ++b){
            if(vf[b]){
                bins[b] = 1;
                minimaze[b] = to_vector(n_arg, b);
                flag_null = 0;
            }
        }
        if(flag_null){
            termVAR* v = new termVAR();
            v->varname = L"0";
            return v->to_string();
        }
        bool flag = 1;
        while(flag){
            flag = 0;
            map<int, bool> buf(bins);
            for(auto i : bins){
                if(buf[i.first])
                for(auto j : bins){
                    if(!buf[j.first])
                        continue;
                    if(i.first == j.first) continue;
                    if(equl(minimaze[i.first], minimaze[j.first])){
                        buf[j.first] = 0;
                        continue;
                    }
                    bool f = 0;
                    auto a = compare(minimaze[i.first], minimaze[j.first], f);
                    if(!f){
                        buf[i.first] = 0;
                        minimaze[j.first] = a;
                        flag = 1;
                        break;
                    }
                }
            }
            bins = buf;
        }
        vector<wstring> variables;
        for(int i = 1; i <= n_arg; i++){
            wstring buf = L"x" + to_wstring(i);
            variables.push_back(buf);
        }
        term* res = 0;
        for(auto a : bins){
            if(!a.second)
                continue;
            term* t = create_dnf(variables, minimaze[a.first]);
            if(!t)
                continue;
            if(res){
                termOR* and_t = new termOR();
                and_t->t1 = res;
                and_t->t2 = t;
                res = and_t;
            }
            else
                res = t;
        }
        if(!res)
        {
            termVAR* v = new termVAR();
            v->varname = L"1";
            res = v;
        }
        return res->to_string();
    }

    wstring main(wstring in_str)
    {
        wstringstream in(in_str);
        wstringstream out;
        uniform_int_distribution<> dis(2, 4);
        int amt_x = dis(gen);
        // auto vf =
        //  Для отладки
        // out << L"Enter a vector of function, or enter 'Generate' if you want to generate vector randomly" << endl;
        wstring input;
        in >> input;
        vector<bool> vf;
        if (input == L"Generate")
        {
            vf = generate_vf(amt_x);
        }
        else
        {
            amt_x = getPowerOfTwo(input.size());
            for (auto el : input)
            {
                if (el == L'0' || el == L'1')
                    vf.push_back(el - L'0');
                else if (el != L')' && el != L',' && el != L'(')
                {
                    out << L"Bad vector" << endl;
                    wstring res = out.str();
                    return res;
                }
            }
        }
        {
            int a = vf.size();
            int b = 0;
            while (a)
            {
                b += a % 2;
                a /= 2;
            }
            if (b > 1)
            {
                out << L"Bad vector" << endl;
                wstring res = out.str();
                return res;
            }
        }

        return getAns(vf);
    }
}