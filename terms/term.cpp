#include "term.hpp"
#include <set>
namespace BoolApp
{
    std::set<wchar_t> dict = {L'&', L'|', L'!', L'=', L'(', L')', L' '};
    std::map<wchar_t, int> prior = {{L'&', 2}, {L'|', 1}, {L'!', 3}, {L'=', 2}}; //'&', '|', '!', '=', '(', ')', ' '};

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
        return t1->to_string() + L" | " + t2->to_string();
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
        return t1->to_string() + L"&" + t2->to_string();
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
        return t1->to_string() + L" = " + t2->to_string();
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
        return L"!" + t1->to_string();
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

    term *parsingVAR(wchar_t *&str, int priority = 0)
    {
        std::wstring buffer = L"";
        wchar_t *start_point = str;
        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                if (*str == L' ')
                    continue;
                if (*str == L'(')
                    return parsing(str, priority);
                if (*str == L'!')
                    return parsing(str, priority);
                if (buffer.size() > 0)
                {
                    if (priority < prior[*str])
                    {
                        priority = prior[*str];
                        str = start_point;
                        return parsing(str, priority);
                    }
                    termVAR *tvar = new termVAR();
                    tvar->varname = buffer;
                    str--;
                    return tvar;
                }
            }
            else
            {
                buffer += *str;
            }
        }
        if (buffer.size() > 0)
        {
            if (buffer.size() > 0)
            {
                termVAR *tvar = new termVAR();
                tvar->varname = buffer;
                str--;
                return tvar;
            }
        }
        return 0;
    }

    term *parsing(wchar_t *&str, int priority = 0)
    {
        std::wstring buffer = L"";
        term *tprev = 0;

        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                /*if (buffer.size() > 0)
                {
                    termVAR *tvar = new termVAR();
                    tvar->varname = buffer;
                    buffer.resize(0);
                    tprev = tvar;
                }*/
                switch (*str)
                {
                case L'|':
                {
                    termOR *t1 = new termOR();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsingVAR(++str, prior[*str]);
                    continue;
                }

                case L'&':
                {
                    termAND *t1 = new termAND();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsingVAR(++str, prior[*str]);
                    continue;
                }

                case L'!':
                {
                    termNOT *t1 = new termNOT();
                    t1->t1 = parsingVAR(++str, prior[*str]);
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
                    termEQUAL *t1 = new termEQUAL();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsingVAR(++str, prior[*str]);
                    continue;
                }
                default:
                    continue;
                }
            }
            else
            {
                tprev = parsingVAR(str, priority);
            }
        }
        /*if (buffer.size() > 0)
        {
            termVAR *tvar = new termVAR();
            tvar->varname = buffer;
            buffer.resize(0);
            tprev = tvar;
        }*/
        str--;
        return tprev;
    }
}
