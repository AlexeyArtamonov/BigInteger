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

namespace Arithmetic_Tests
{
	using leart::BigInteger;

	TEST_CLASS(Addition)
	{
		TEST_METHOD(Negative_Negative)
		{
			BigInteger a = "-110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a + b, BigInteger("-123254"));
		}
		TEST_METHOD(Negative_Postivice)
		{

			BigInteger a = "-110002";
			BigInteger b = "13252";

			Assert::AreEqual(a + b, BigInteger("-96750"));
		}
		TEST_METHOD(Positive_Negative)
		{

			BigInteger a = "110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a + b, BigInteger("96750"));
		}
		TEST_METHOD(Positive_Positive)
		{

			BigInteger a = "110002";
			BigInteger b = "13252";

			Assert::AreEqual(a + b, BigInteger("123254"));
		}
	};
	TEST_CLASS(Substraction)
	{
		TEST_METHOD(Negative_Negative)
		{
			BigInteger a = "-110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a - b, BigInteger("-96750"));
		}
		TEST_METHOD(Negative_Postivice)
		{

			BigInteger a = "-110002";
			BigInteger b = "13252";

			Assert::AreEqual(a - b, BigInteger("-123254"));
		}
		TEST_METHOD(Positive_Negative)
		{

			BigInteger a = "110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a - b, BigInteger("123254"));
		}
		TEST_METHOD(Positive_Positive)
		{

			BigInteger a = "110002";
			BigInteger b = "13252";

			Assert::AreEqual(a - b, BigInteger("96750"));
		}
	};
	TEST_CLASS(Multiplication)
	{
		TEST_METHOD(Negative_Negative)
		{
			BigInteger a = "-110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a * b, BigInteger("1457746504"));
		}
		TEST_METHOD(Negative_Postivice)
		{

			BigInteger a = "-110002";
			BigInteger b = "13252";

			Assert::AreEqual(a * b, BigInteger("-1457746504"));
		}
		TEST_METHOD(Positive_Negative)
		{

			BigInteger a = "110002";
			BigInteger b = "-13252";

			Assert::AreEqual(a * b, BigInteger("-1457746504"));
		}
		TEST_METHOD(Positive_Positive)
		{

			BigInteger a = "110002";
			BigInteger b = "13252";

			Assert::AreEqual(a * b, BigInteger("1457746504"));
		}
	};
}