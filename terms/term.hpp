#include <string>
#include <map>

namespace BoolApp
{
    struct termData
    {
        std::map<std::string, bool> nametovar;
    };

    struct term
    {
        virtual bool calculate(termData td) = 0;
    };

    term *parsing(std::string str);

    struct termOR : term
    {
        term *t1;
        term *t2;

        bool calculate(termData td) override;
    };

    struct termAND : term
    {
        term *t1;
        term *t2;

        bool calculate(termData td) override;
    };

    struct termNOT : term
    {
        term *t1;

        bool calculate(termData td) override;
    };

    struct termVAR : term
    {
        std::string varname;

        bool calculate(termData td) override;
    };

    struct termEQUAL : term
    {
        term *t1;
        term *t2;

        bool calculate(termData td) override;
    };
}
