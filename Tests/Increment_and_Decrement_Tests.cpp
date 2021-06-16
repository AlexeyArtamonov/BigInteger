#include "../Headers/BigInteger.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
namespace Microsoft {
	namespace VisualStudio {
		namespace CppUnitTestFramework
		{
			template<> inline std::wstring ToString<leart::BigInteger>(const leart::BigInteger& t)
			{
				return t.Get_Wstring_Representation();
			}
		}
	}
}

namespace Increment_and_Decrement_Tests
{
	using leart::BigInteger;
	// All tests below are designed for base = 1'000'000'000
	TEST_CLASS(Increment)
	{
		#pragma region Negative_number_Increment
		TEST_METHOD(Negative_number1)
		{
			BigInteger a = -1;
			a++;
			Assert::AreEqual(a, (BigInteger)0);
		}
		TEST_METHOD(Negative_number2)
		{
			BigInteger a = -3;
			a++;
			Assert::AreEqual(a, (BigInteger)-2);
		}
		TEST_METHOD(Negative_number3)
		{
			BigInteger a = -999'999'999;
			a++;
			Assert::AreEqual(a, (BigInteger)-999'999'998);
		}
		TEST_METHOD(Negative_number4)
		{
			BigInteger a = -1'000'000'000;
			a++;
			Assert::AreEqual(a, (BigInteger)-999'999'999);
		}
		TEST_METHOD(Negative_number5)
		{
			BigInteger a = -1'000'000'001;
			a++;
			Assert::AreEqual(a, (BigInteger)-1'000'000'000);
		}
		#pragma endregion
	};
	
	TEST_CLASS(Decrement)
	{
		#pragma region Negative_number_Decrement
		TEST_METHOD(Negative_number1)
		{
			BigInteger a = -1;
			a--;
			Assert::AreEqual(a, (BigInteger)-2);
		}
		TEST_METHOD(Negative_number2)
		{
			BigInteger a = -3;
			a--;
			Assert::AreEqual(a, (BigInteger)-4);
		}
		TEST_METHOD(Negative_number3)
		{
			BigInteger a = -999'999'999;
			a--;
			Assert::AreEqual(a, (BigInteger)-1'000'000'000);
		}
		TEST_METHOD(Negative_number4)
		{
			BigInteger a = -1'000'000'000;
			a--;
			Assert::AreEqual(a, (BigInteger)-1'000'000'001);
		}
		TEST_METHOD(Negative_number5)
		{
			BigInteger a = -1'000'000'001;
			a--;
			Assert::AreEqual(a, (BigInteger)-1'000'000'002);
		}
		#pragma endregion
	};
};