#include <iostream>
#include <chrono>

#include "Headers/BigInteger.h"

int main()
{
	using namespace leart;
	unsigned int n = 0;
	std::cin >> n;

	auto start = std::chrono::high_resolution_clock::now();

	BigInteger factorial = 1;
	for (size_t i = 1; i <= n; i++)
	{
		factorial *= i;
	}
	std::cout << factorial << std::endl;

	auto stop = std::chrono::high_resolution_clock::now();

	std::cout << "Execution Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << "ms" << std::endl;
	//Slow
}
