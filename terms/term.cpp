#include "term.hpp"
#include <set>
namespace BoolApp
{
    std::set<char> dict = {'&', '|', '!', '=', '(', ')', ' '};

    bool termOR::calculate(termData td)
    {
        return t1->calculate(td) || t2->calculate(td);
    }

    bool termAND::calculate(termData td)
    {
        return t1->calculate(td) && t2->calculate(td);
    }

    bool termEQUAL::calculate(termData td)
    {
        return t1->calculate(td) == t2->calculate(td);
    }

    bool termNOT::calculate(termData td)
    {
        return !t1->calculate(td);
    }

    bool termVAR::calculate(termData td)
    {
        return td.nametovar[varname];
    }

    term *parsing(char *str)
    {
        std::string buffer = "";
        term *tprev = 0;

        for (; *str; str++)
        {
            if (dict.find(*str) != dict.end())
            {
                if (buffer.size() > 0)
                {
                    termVAR *tvar = new termVAR();
                    tvar->varname = buffer;
                    buffer.resize(0);
                    tprev = tvar;
                }
                switch (*str)
                {
                case '|':
                {
                    termOR *t1 = new termOR();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsing(++str);
                    continue;
                }

                case '&':
                {
                    termAND *t1 = new termAND();
                    t1->t1 = tprev;
                    tprev = t1;
                    t1->t2 = parsing(++str);
                    continue;
                }

                case '!':
                {
                    termNOT *t1 = new termNOT();
                    t1->t1 = parsing(++str);
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
                    t1->t2 = parsing(++str);
                    continue;
                }
                default:
                    continue;
                }
            }
            else
            {
                buffer += *str;
            }
        }
        return nullptr;
    }
}
