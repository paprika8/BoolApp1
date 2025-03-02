#include "term.hpp"
#include <iostream>
#include <string>

using namespace std;
using namespace BoolApp;

void log(term *test, int a, int b){
    termData data;
    data.nametovar["x1"] = a;
    data.nametovar["x2"] = b;

    cout << test->calculate(data);
}

int main()
{

    string str = "x1 & x2 | !x1 & !x2";
    char * it = str.data();
    term *test = parsing((char *&)it);

    log(test, 0, 0);
    log(test, 0, 1);
    log(test, 1, 0);
    log(test, 1, 1);
}