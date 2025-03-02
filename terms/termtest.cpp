#include "term.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace BoolApp;

int main()
{

    string str = "x1 & x2";

    term *test = parsing((char *&)str.data());
}