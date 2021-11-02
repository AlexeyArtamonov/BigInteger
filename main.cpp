#include <iostream>
#include "Headers/BigInteger.h"

int main()
{
	using namespace leart;
	BigInteger a = 43;
	BigInteger b = std::string("3243");
	std::cout << a - b;
}
