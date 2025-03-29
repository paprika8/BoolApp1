#include "term.h"
#include <set>
namespace BoolApp
{
    std::set<wchar_t> dict = {L'&', L'|', L'!', L'=', L'(', L')', L' '};
    std::map<wchar_t, int> prior = {{L'&', 2}, {L'|', 1}, {L'!', 3}, {L'=', 0}}; //'&', '|', '!', '=', '(', ')', ' '};

    bool termOR::calculate(termData &td)
    {
        return t1->calculate(td) || t2->calculate(td);
    }

    void termOR::get_name_list(std::set<std::wstring> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::wstring termOR::to_string()
    {
        return L"(" + t1->to_string() + L" | " + t2->to_string()+ L")";
    }

    bool termAND::calculate(termData &td)
    {
        return t1->calculate(td) && t2->calculate(td);
    }

    void termAND::get_name_list(std::set<std::wstring> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::wstring termAND::to_string()
    {
        return L"(" + t1->to_string() + L"&" + t2->to_string()+ L")";
    }

    bool termEQUAL::calculate(termData &td)
    {
        return t1->calculate(td) == t2->calculate(td);
    }

    void termEQUAL::get_name_list(std::set<std::wstring> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::wstring termEQUAL::to_string()
    {
        return L"(" + t1->to_string() + L" = " + t2->to_string()+ L")";
    }

    bool termNOT::calculate(termData &td)
    {
        return !t1->calculate(td);
    }

    void termNOT::get_name_list(std::set<std::wstring> &v)
    {
        t1->get_name_list(v);
    }

    std::wstring termNOT::to_string()
    {
        return L"(!" + t1->to_string() + L")";
    }

    bool termVAR::calculate(termData &td)
    {
        return td.nametovar[varname];
    }

    void termVAR::get_name_list(std::set<std::wstring> &v)
    {
        v.insert(varname);
    }

    std::wstring termVAR::to_string()
    {
        return varname;
    }

    term *parsingLit(wchar_t *&str, int priority = 0){
        std::wstring buffer = L"";
        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                termVAR *tvar = new termVAR();
                tvar->varname = buffer;
                str--;
                return tvar;
            }
            else
            {
                buffer += *str;
            }
        }
        termVAR *tvar = new termVAR();
        tvar->varname = buffer;
        str--;
        return tvar;
    }

    term *parsing(wchar_t *&str, int priority = 0){
        std::wstring buffer = L"";
        term *tprev = 0;

        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                switch (*str)
                {
                case L'|':
                {
                    if(priority > 1){
                        str--;
                        return tprev;
                    }
                    termOR *t1 = new termOR();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsing(++str, 1);
                    continue;
                }

                case L'&':
                {
                    if(priority > 2){
                        str--;
                        return tprev;
                    }
                    termAND *t1 = new termAND();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsing(++str, 2);
                    continue;
                }

                case L'!':
                {
                    termNOT *t1 = new termNOT();
                    t1->t1 = parsing(++str, 3);
                    tprev = t1;
                    continue;
                }

                case L'(':
                {
                    tprev = parsing(++str);
                    continue;
                }
                case L')':
                {
                    return tprev;
                }
                case L'=':
                {
                    if(priority > 0){
                        str--;
                        return tprev;
                    }
                    termEQUAL *t1 = new termEQUAL();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsing(++str, 0);
                    continue;
                }
                default:
                    continue;
                }
            }
            else
            {
                tprev = parsingLit(str, priority);
            }
        }
        str--;
        return tprev;
    }
}
