#include <iostream>
#include "Headers/BigInteger.h"

int main()
{
	using namespace leart;
	BigInteger a = 43;
	BigInteger b("57");
	std::cout <<a + b;
}
