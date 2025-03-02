#include "term.hpp"
#include <set>
namespace BoolApp
{
    std::set<char> dict = {'&', '|', '!', '=', '(', ')', ' '};
    std::map<char, int> prior = {{'&', 2}, {'|', 1}, {'!', 3}, {'=', 2}};//'&', '|', '!', '=', '(', ')', ' '};

    bool termOR::calculate(termData &td)
    {
        return t1->calculate(td) || t2->calculate(td);
    }

    bool termAND::calculate(termData &td)
    {
        return t1->calculate(td) && t2->calculate(td);
    }

    bool termEQUAL::calculate(termData &td)
    {
        return t1->calculate(td) == t2->calculate(td);
    }

    bool termNOT::calculate(termData &td)
    {
        return !t1->calculate(td);
    }

    bool termVAR::calculate(termData &td)
    {
        return td.nametovar[varname];
    }

    term* parsingVAR(char *&str, int priority = 0){
        std::string buffer = "";
        char* start_point = str;
        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                if(*str == ' ')
                    continue;
                if(*str == '(')
                    return parsing(str, priority);
                if(*str == '!')
                    return parsing(str, priority);
                if (buffer.size() > 0)
                {
                    if(priority < prior[*str]){
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
