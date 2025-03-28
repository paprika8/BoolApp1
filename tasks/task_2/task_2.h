#pragma once
#include "..\..\terms\term.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>
#include <sstream>

using namespace std;

namespace task2
{
	int countDigits(int number);

	int twoInPower(int power);

	int getPowerOfTwo(size_t n);

	//| x1 | x2 | x3 | f |
	//|  0 |  0 |  0 | 0 |
	//|  0 |  0 |  0 | 0 |
	//|  0 |  0 |  1 | 0 |
	//|  0 |  0 |  1 | 0 |
	wstring main(wstring in);
}