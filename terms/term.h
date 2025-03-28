#include <string>
#include <set>
#include <map>

namespace BoolApp
{
    struct termData
    {
        std::map<std::wstring, bool> nametovar;
        termData()
        {
            nametovar[L"0"] = 0;
            nametovar[L"1"] = 1;
        }
    };

    struct term
    {
        virtual void get_name_list(std::set<std::wstring> &v) = 0;

        virtual bool calculate(termData &td) = 0;

        virtual std::wstring to_string() = 0;
    };

    term *parsing(wchar_t *&str, int priority = 0);

    struct termOR : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;
        void get_name_list(std::set<std::wstring> &v) override;

        std::wstring to_string() override;
    };

    struct termAND : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::wstring> &v) override;

        std::wstring to_string() override;
    };

    struct termNOT : term
    {
        term *t1;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::wstring> &v) override;

        std::wstring to_string() override;
    };

    struct termVAR : term
    {
        std::wstring varname;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::wstring> &v) override;

        std::wstring to_string() override;
    };

    struct termEQUAL : term
    {
        term *t1;
        term *t2;

        bool calculate(termData &td) override;

        void get_name_list(std::set<std::wstring> &v) override;

        std::wstring to_string() override;
    };
}
