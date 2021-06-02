#pragma once
#include <vector>
#include <complex>
namespace leart
{
	using cmplxtype = double;
	using vocmplx = std::vector<std::complex<cmplxtype>>;
	class FFT
	{
	private:
		FFT();
		FFT(const FFT&) = delete;
		static vocmplx roots;
		static int rootsUsage;
	public:
		static vocmplx FFT_(const vocmplx& vec);
		static vocmplx RFFT_(const vocmplx& vec);
	};
}