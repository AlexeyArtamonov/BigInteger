#include "../Headers/BigInteger.h"
#include "CppUnitTest.h"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<leart::BigInteger>(const leart::BigInteger& t)
			{
				return t.getWstring();
			}
		}
	}
}

namespace Edge_Cases
{
	using leart::BigInteger;

	TEST_CLASS(Edge_Cases)
	{
		TEST_METHOD(Zero_Zero_Mul)
		{
			BigInteger a = 0;
			Assert::AreEqual(a * a, BigInteger("0"));
		}
		TEST_METHOD(Big_Add)
		{
			BigInteger a = "121253289763896194356891475329741984689456893146758935689373897298631489632";
			BigInteger b = "687932758613782855649078245278494879024756314583649074867489563489537869035";

			Assert::AreEqual(a + b, BigInteger("809186048377679050005969720608236863714213207730408010556863460788169358667"));
		}
		TEST_METHOD(Big_Sub)
		{
			BigInteger a = "121253289763896194356891475329741984689456893146758935689373897298631489632";
			BigInteger b = "687932758613782855649078245278494879024756314583649074867489563489537869035";

			Assert::AreEqual(a - b, BigInteger("-566679468849886661292186769948752894335299421436890139178115666190906379403"));
		}
		TEST_METHOD(Big_Mul)
		{
			BigInteger a = "123512352624236326364333634";
			BigInteger b = "1351464284684245243573573";

			Assert::AreEqual(a * b, BigInteger("166922533288981807662480101265259932351172997454282"));
		}
	};
}