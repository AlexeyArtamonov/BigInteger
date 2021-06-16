/*
MIT License

Copyright (c) 2021 Alexey

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "../Headers/FFT.h"

namespace leart
{
	
	vocmplx FFT::FFT_(const vocmplx& vec)
	{
		int n = vec.size();
		int k = 0;

		while ((1 << k) < n) k++;

		std::vector<int> rev(n);
		rev[0] = 0;
		int high1 = -1;

		for (int i = 1; i < n; i++) 
		{
			if ((i & (i - 1)) == 0)
				high1++;
			rev[i] = rev[i ^ (1 << high1)];
			rev[i] |= (1 << (k - high1 - 1));
		}

		vocmplx	roots(n);
		for (int i = 0; i < n; i++)
		{
			double temp = 2 * 3.14159265358979323846 * i / n;
			roots[i] = std::complex <cmplxtype>(std::cos(temp), std::sin(temp));
		}

		vocmplx cur(n);
		for (int i = 0; i < n; i++)
			cur[i] = vec[rev[i]];

		for (int len = 1; len < n; len <<= 1)
		{
			vocmplx ncur(n);
			int rstep = roots.size() / (len * 2);
			for (int pdest = 0; pdest < n;)
			{
				int p1 = pdest;
				for (int i = 0; i < len; i++)
				{
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