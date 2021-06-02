#include "FFT.h"

namespace leart
{
	
	vocmplx FFT::FFT_(const vocmplx& vec)
	{
		int n = vec.size();
		int k = 0;

		while ((1 << k) < n) k++;

		std::vector<int> rev(n); //Массив для хранения перевернутых индексов
		rev[0] = 0;
		int high1 = -1;

		//Переворот битов
		for (int i = 1; i < n; i++) 
		{
			if ((i & (i - 1)) == 0) // Проверка на степень двойки. Если i ей является, то i-1 будет состоять из кучи единиц.
				high1++;
			rev[i] = rev[i ^ (1 << high1)]; // Переворачиваем остаток
			rev[i] |= (1 << (k - high1 - 1)); // Добавляем старший бит
		}

		//Предвычисление корней
			vocmplx	roots(n);
			for (int i = 0; i < n; i++)
			{
				double temp = 2 * 3.14159265358979323846 * i / n;
				roots[i] = std::complex <cmplxtype>(std::cos(temp), std::sin(temp));
			}

		vocmplx cur(n);
		for (int i = 0; i < n; i++)
			cur[i] = vec[rev[i]];

		for (int len = 1; len < n; len <<= 1) {
			vocmplx ncur(n);
			int rstep = roots.size() / (len * 2);
			for (int pdest = 0; pdest < n;) {
				int p1 = pdest;
				for (int i = 0; i < len; i++) {
					std::complex<cmplxtype> val = roots[i * rstep] * cur[p1 + len];
					ncur[pdest] = cur[p1] + val;
					ncur[pdest + len] = cur[p1] - val;
					pdest++, p1++;
				}
				pdest += len;
			}
			cur.swap(ncur);
		}
		return cur;

	}
	vocmplx FFT::RFFT_(const vocmplx& vec)
	{
		vocmplx res = FFT::FFT_(vec);
		for (int i = 0; i < (int)res.size(); i++)
			res[i] /= vec.size();
		reverse(res.begin() + 1, res.end());
		return res;
	}
}