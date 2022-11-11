#include <iostream>
#include <chrono>

#include "Headers/BigInteger.h"

#ifdef _WIN32
#include "windows.h"
#include "psapi.h"
#endif




int main()
{
	using namespace leart;
	unsigned int n = 0;
	std::cin >> n;

	auto start = std::chrono::high_resolution_clock::now();
#ifdef  _WIN32
	PROCESS_MEMORY_COUNTERS_EX pmc;
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T m_start = pmc.PrivateUsage;
#endif
	BigInteger factorial = 1;
	for (size_t i = 1; i <= n; i++)
	{
		factorial *= i;
	}
	std::cout << factorial << std::endl;

	auto stop = std::chrono::high_resolution_clock::now();
#ifdef  _WIN32
	GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
	SIZE_T m_end = pmc.PrivateUsage;
#endif
	std::cout << "Execution Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
	std::cout << "ms" << std::endl;
#ifdef _WIN32
	std::cout << "Memory Usage: " << (m_end - m_start) / 1024 << "KiB" << std::endl;
#endif
	//Slow
}
