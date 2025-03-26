#include "term.hpp"
#include <set>
namespace BoolApp
{
    std::set<char> dict = {'&', '|', '!', '=', '(', ')', ' '};
    std::map<char, int> prior = {{'&', 2}, {'|', 1}, {'!', 3}, {'=', 2}}; //'&', '|', '!', '=', '(', ')', ' '};

    bool termOR::calculate(termData &td)
    {
        return t1->calculate(td) || t2->calculate(td);
    }

    void termOR::get_name_list(std::set<std::string> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::string termOR::to_string()
    {
        return t1->to_string() + " | " + t2->to_string();
    }

    bool termAND::calculate(termData &td)
    {
        return t1->calculate(td) && t2->calculate(td);
    }

    void termAND::get_name_list(std::set<std::string> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::string termAND::to_string()
    {
        return t1->to_string() + "&" + t2->to_string();
    }

    bool termEQUAL::calculate(termData &td)
    {
        return t1->calculate(td) == t2->calculate(td);
    }

    void termEQUAL::get_name_list(std::set<std::string> &v)
    {
        t1->get_name_list(v);
        t2->get_name_list(v);
    }

    std::string termEQUAL::to_string()
    {
        return t1->to_string() + " = " + t2->to_string();
    }

    bool termNOT::calculate(termData &td)
    {
        return !t1->calculate(td);
    }

    void termNOT::get_name_list(std::set<std::string> &v)
    {
        t1->get_name_list(v);
    }

    std::string termNOT::to_string()
    {
        return "!" + t1->to_string();
    }

    bool termVAR::calculate(termData &td)
    {
        return td.nametovar[varname];
    }

    void termVAR::get_name_list(std::set<std::string> &v)
    {
        v.insert(varname);
    }

    std::string termVAR::to_string()
    {
        return varname;
    }

    term *parsingVAR(char *&str, int priority = 0)
    {
        std::string buffer = "";
        char *start_point = str;
        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                if (*str == ' ')
                    continue;
                if (*str == '(')
                    return parsing(str, priority);
                if (*str == '!')
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

    term *parsing(char *&str, int priority = 0)
    {
        std::string buffer = "";
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
                case '|':
                {
                    termOR *t1 = new termOR();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsingVAR(++str, prior[*str]);
                    continue;
                }

                case '&':
                {
                    termAND *t1 = new termAND();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsingVAR(++str, prior[*str]);
                    continue;
                }

                case '!':
                {
                    termNOT *t1 = new termNOT();
                    t1->t1 = parsingVAR(++str, prior[*str]);
                    tprev = t1;
                    continue;
                }

                case '(':
                {
                    tprev = parsing(++str);
                    continue;
                }
                case ')':
                {
                    return tprev;
                }
                case '=':
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
