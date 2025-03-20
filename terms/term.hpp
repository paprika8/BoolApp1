#include <string>
#include <set>
#include <map>

namespace BoolApp
{
    struct termData
    {
        std::map<std::string, bool> nametovar;
        termData()
        {
            nametovar["0"] = 0;
            nametovar["1"] = 1;
        }
    };

    struct term
    {
        virtual void get_name_list(std::set<std::string> &v) = 0;

        virtual bool calculate(termData &td) = 0;
    };

    term *parsing(char *&str, int priority = 0);

    struct termOR : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;
        void get_name_list(std::set<std::string> &v) override;
    };

    struct termAND : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::string> &v) override;
    };

    struct termNOT : term
    {
        term *t1;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::string> &v) override;
    };

    struct termVAR : term
    {
        std::string varname;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::string> &v) override;
    };

    struct termEQUAL : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::string> &v) override;
    };
}
