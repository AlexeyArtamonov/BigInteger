#include "BigInteger.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Comparsion_Operators_Tests
{
	using leart::BigInteger;

	TEST_CLASS(Equal)
	{
		TEST_METHOD(Test1)
		{
			BigInteger a = 5;
			BigInteger b = 5;
			Assert::AreEqual(a == b, true);
		}
		TEST_METHOD(Test2)
		{
			BigInteger a = 4;
			BigInteger b = 5;
			Assert::AreEqual(a == b, false);
		}
		TEST_METHOD(Test3)
		{
			BigInteger a = 5;
			BigInteger b = 4;
			Assert::AreEqual(a == b, false);
		}
		//-------------------------
		TEST_METHOD(Test4)
		{
			BigInteger a = -4;
			BigInteger b = 5;
			Assert::AreEqual(a == b, false);

			a = 4;
			b = -5;
			Assert::AreEqual(a == b, false);

			a = -4;
			b = -5;
			Assert::AreEqual(a == b, false);
		}
		TEST_METHOD(Test5)
		{
			BigInteger a = -5;
			BigInteger b = 5;
			Assert::AreEqual(a == b, false);

			a = 5;
			b = -5;
			Assert::AreEqual(a == b, false);

			a = -5;
			b = -5;
			Assert::AreEqual(a == b, true);
		}
	};
	TEST_CLASS(Not_equal)
	{
		TEST_METHOD(Test1)
		{
			BigInteger a = 5;
			BigInteger b = 5;
			Assert::AreEqual(a != b, false);
		}
		TEST_METHOD(Test2)
		{
			BigInteger a = 4;
			BigInteger b = 5;
			Assert::AreEqual(a != b, true);
		}
		TEST_METHOD(Test3)
		{
			BigInteger a = 5;
			BigInteger b = 4;
			Assert::AreEqual(a != b, true);
		}
		//-------------------------
		TEST_METHOD(Test4)
		{
			BigInteger a = -4;
			BigInteger b = 5;
			Assert::AreEqual(a != b, true);

			a = 4;
			b = -5;
			Assert::AreEqual(a != b, true);

			a = -4;
			b = -5;
			Assert::AreEqual(a != b, true);
		}
		TEST_METHOD(Test5)
		{
			BigInteger a = -5;
			BigInteger b = 5;
			Assert::AreEqual(a != b, true);

			a = 5;
			b = -5;
			Assert::AreEqual(a != b, true);

			a = -5;
			b = -5;
			Assert::AreEqual(a != b, false);
		}
	};
	TEST_CLASS(Bigger_Than)
	{
	public:
	#pragma region UnsignedTests
		TEST_METHOD(UnsignedTest1)
		{
			BigInteger a = 6;
			BigInteger b = 5;
			Assert::AreEqual(a > b, true);	
		}
		TEST_METHOD(UnsignedTest2)
		{
			BigInteger a = 5;
			BigInteger b = 6;
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(UnsignedTest3)
		{
			BigInteger a = 5;
			BigInteger b = 5;
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(UnsignedTest4)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "100000000000000000000000";
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(UnsignedTest5)
		{
			BigInteger a = "100000000000000000000000";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(UnsignedTest6)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a > b, false);
		}
	#pragma endregion
	#pragma region SignedTests
		TEST_METHOD(SignedTest1)
		{
			BigInteger a = -6;
			BigInteger b = 5;
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest2)
		{
			BigInteger a = 6;
			BigInteger b = -5;
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest3)
		{
			BigInteger a = -6;
			BigInteger b = -5;
			Assert::AreEqual(a > b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest4)
		{
			BigInteger a = -5;
			BigInteger b = 6;
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest5)
		{
			BigInteger a = 5;
			BigInteger b = -6;
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest6)
		{
			BigInteger a = -5;
			BigInteger b = -6;
			Assert::AreEqual(a > b, true);
		}
		//-------------------------------
		TEST_METHOD(SignedTest7)
		{
			BigInteger a = -5;
			BigInteger b = 5;
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest8)
		{
			BigInteger a = 5;
			BigInteger b = -5;
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest9)
		{
			BigInteger a = -5;
			BigInteger b = -5;
			Assert::AreEqual(a > b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest10)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "100000000000000000000000";
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest11)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "-100000000000000000000000";
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest12)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "-100000000000000000000000";
			Assert::AreEqual(a > b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest13)
		{
			BigInteger a = "-100000000000000000000000";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest14)
		{
			BigInteger a = "100000000000000000000000";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest15)
		{
			BigInteger a = "-100000000000000000000000";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a > b, true);
		}
		//-------------------------------
		TEST_METHOD(SignedTest16)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a > b, false);
		}
		TEST_METHOD(SignedTest17)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a > b, true);
		}
		TEST_METHOD(SignedTest18)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a > b, false);
		}
	#pragma endregion
	};
	TEST_CLASS(Lesser_Than)
	{
	public:
	#pragma region UnsignedTests
		TEST_METHOD(UnsignedTest1)
		{
			BigInteger a = 6;
			BigInteger b = 5;
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(UnsignedTest2)
		{
			BigInteger a = 5;
			BigInteger b = 6;
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(UnsignedTest3)
		{
			BigInteger a = 5;
			BigInteger b = 5;
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(UnsignedTest4)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "100000000000000000000000";
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(UnsignedTest5)
		{
			BigInteger a = "100000000000000000000000";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(UnsignedTest6)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a < b, false);
		}
	#pragma endregion
	#pragma region SignedTests
		TEST_METHOD(SignedTest1)
		{
			BigInteger a = -6;
			BigInteger b = 5;
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest2)
		{
			BigInteger a = 6;
			BigInteger b = -5;
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest3)
		{
			BigInteger a = -6;
			BigInteger b = -5;
			Assert::AreEqual(a < b, true);
		}
		//-------------------------------
		TEST_METHOD(SignedTest4)
		{
			BigInteger a = -5;
			BigInteger b = 6;
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest5)
		{
			BigInteger a = 5;
			BigInteger b = -6;
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest6)
		{
			BigInteger a = -5;
			BigInteger b = -6;
			Assert::AreEqual(a < b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest7)
		{
			BigInteger a = -5;
			BigInteger b = 5;
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest8)
		{
			BigInteger a = 5;
			BigInteger b = -5;
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest9)
		{
			BigInteger a = -5;
			BigInteger b = -5;
			Assert::AreEqual(a < b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest10)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "100000000000000000000000";
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest11)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "-100000000000000000000000";
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest12)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "-100000000000000000000000";
			Assert::AreEqual(a < b, true);
		}
		//-------------------------------
		TEST_METHOD(SignedTest13)
		{
			BigInteger a = "-100000000000000000000000";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest14)
		{
			BigInteger a = "100000000000000000000000";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest15)
		{
			BigInteger a = "-100000000000000000000000";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a < b, false);
		}
		//-------------------------------
		TEST_METHOD(SignedTest16)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "123456789101234554637458";
			Assert::AreEqual(a < b, true);
		}
		TEST_METHOD(SignedTest17)
		{
			BigInteger a = "123456789101234554637458";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a < b, false);
		}
		TEST_METHOD(SignedTest18)
		{
			BigInteger a = "-123456789101234554637458";
			BigInteger b = "-123456789101234554637458";
			Assert::AreEqual(a < b, false);
		}
	#pragma endregion
	};
}
