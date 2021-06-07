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

#include <string>
#include "BigInteger.h"

namespace leart
{
	BigInteger::BigInteger()
	{
		SetArray("0");
	}
	BigInteger::BigInteger(const long long number)
	{
		SetArray(number);
	}
	BigInteger::BigInteger(const std::string& s_number)
	{
		SetArray(s_number);
	}
	/*BigInteger::BigInteger(const char* s_number)
	{
		SetArray(s_number);
	}*/
	BigInteger::BigInteger(const BigInteger& copy)
	{
		sign = copy.sign;
		arr = copy.arr;
	}

	BigInteger::type& BigInteger::operator[] (const int index)
	{
		return arr[index];
	}
	BigInteger::type BigInteger::operator[] (const int index) const
	{
		return arr[index];
	}


	//Public functions------------------------------------------------------------------------------
	std::istream& operator>>(std::istream& input, BigInteger& number)
	{
		std::string temp;
		input >> temp;
		number.SetArray(temp);
		return input;
	}
	std::ostream& operator<<(std::ostream& output, const BigInteger& number)
	{
		return (output << number.Get_String_Representation());
	}

	BigInteger operator+ (const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger result;

		int IsgreaterCallResult = BigInteger::is_greater(first_number, second_number);
		if (first_number.sign == 1 && second_number.sign == 1)
		{
			if (first_number.size() >= second_number.size())
				result = BigInteger::Add(first_number, second_number);
			else
				result = BigInteger::Add(second_number, first_number);

			result.sign = 1;
		}
		else if (first_number.sign == 1 && second_number.sign == 0)
		{
			if (IsgreaterCallResult == 2)
			{
				result.SetArray(0);
				result.sign = 1;
			}
			else if (IsgreaterCallResult == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result.sign = 1;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result.sign = 0;
			}
		}
		else if (first_number.sign == 0 && second_number.sign == 1)
		{
			if (IsgreaterCallResult == 2)
			{
				result.SetArray(0);
				result.sign = 1;
			}
			else if (IsgreaterCallResult == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result.sign = 0;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result.sign = 1;
			}
		}
		else
		{
			if (first_number.size() > second_number.size())
				result = BigInteger::Add(first_number, second_number);
			else
				result = BigInteger::Add(second_number, first_number);
			result.sign = 0;
		}

		return result;
	}
	BigInteger operator- (const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger result;

		if (first_number.sign == 1 && second_number.sign == 1)  
		{
			if (BigInteger::is_greater(first_number, second_number) == 2)
			{
				result.SetArray(0);
				result.sign = 1;
			}
			else if (BigInteger::is_greater(first_number, second_number) == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result.sign = 1;
			}
			else
			{
				result = BigInteger::Sub(second_number,first_number);
				result.sign = 0;
			}
		}
		else if (first_number.sign == 0 && second_number.sign == 1)
		{

			if (BigInteger::is_greater(first_number, second_number) == 1)
			{
				result = BigInteger::Add(first_number, second_number);
				result.sign = 0;
			}
			else
			{
				result = BigInteger::Add(second_number, first_number);
				result.sign = 0;
			}
		}
		else if (first_number.sign == 1 && second_number.sign == 0)
		{
			if (BigInteger::is_greater(first_number, second_number) == 1)
			{
				result = BigInteger::Add(first_number, second_number);
				result.sign = 1;
			}
			else
			{
				result = BigInteger::Add(second_number, first_number);
				result.sign = 1;
			}
		}
		else
		{
			if (BigInteger::is_greater(first_number, second_number) == 2)
			{
				result.SetArray(0);
				result.sign = 1;
			}
			else if (BigInteger::is_greater(first_number, second_number) == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result.sign = 0;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result.sign = 1;
			}
		}

		return result;

	}
	BigInteger operator* (const BigInteger& first_number, const BigInteger& second_number)
	{
		if (first_number == 0 || second_number == 0)
			return 0;
		else
		{
			if (first_number == 1)
				return second_number;
			else if (second_number == 1)
				return first_number;
			else
			{
				BigInteger result = BigInteger::Mul(first_number, second_number);
				result.sign = !(first_number.sign ^ second_number.sign);
				return result;
			}
		}
		
	}

	//TODO: Needs test
	BigInteger operator+ (const BigInteger& first_number, const long long second_number)
	{
		if (second_number < 0)
			return operator-(first_number, -second_number);

		if (second_number > BigInteger::base)
			return operator+ (first_number, (BigInteger)second_number);

		return BigInteger::Add(first_number, second_number);
	}
	BigInteger operator- (const BigInteger& first_number, const long long second_number)
	{
		if (second_number < 0)
			return operator+(first_number, -second_number);

		//TODO: Redo after sleep
		BigInteger result;
		if (first_number.size() > 1)
		{
			result = BigInteger::Sub(first_number, second_number);
			result.sign = 1;
		}
		else
		{
			if (second_number < BigInteger::base)
			{
				if (first_number[0] > second_number)
				{
					result = BigInteger::Sub(first_number, second_number);
					result.sign = 1;
				}
				else
				{
					result = BigInteger::Sub((BigInteger)second_number, first_number);
					result.sign = 0;
				}
			}
			else
				result = operator- (first_number, (BigInteger)second_number);
		}
		return result;
	}
	BigInteger operator* (const BigInteger& first_number, const long long second_number)
	{
		BigInteger result = BigInteger::Mul(first_number,second_number);
		result.sign = !(first_number.sign ^ (second_number >= 0? 1 : 0));
		return result;
	}

	BigInteger operator* (const long long first_number, const BigInteger& second_number)
	{
		return operator* (second_number, first_number);
	}

	bool operator== (const BigInteger& first_number, const BigInteger& second_number)
	{
		return BigInteger::is_greater(first_number, second_number) == 2;
	}
	bool operator!= (const BigInteger& first_number, const BigInteger& second_number)
	{
		return !(BigInteger::is_greater(first_number, second_number) == 2);
	}
	bool operator> (const BigInteger& first_number, const BigInteger& second_number)
	{
		if (BigInteger::is_greater(first_number, second_number) == 1)
			return true;
		else
			return false;
	}
	bool operator< (const BigInteger& first_number, const BigInteger& second_number)
	{
		if (BigInteger::is_greater(first_number, second_number) == 0)
			return true;
		else
			return false;
	}
	bool operator>= (const BigInteger& first_number, const BigInteger& second_number)
	{
		if (BigInteger::is_greater(first_number, second_number) == 1
			|| BigInteger::is_greater(first_number, second_number) == 2)
			return true;
		else
			return false;
	}
	bool operator<= (const BigInteger& first_number, const BigInteger& second_number)
	{
		if (BigInteger::is_greater(first_number, second_number) == 0
			|| BigInteger::is_greater(first_number, second_number) == 2)
			return true;
		else
			return false;
	}

	BigInteger& BigInteger::operator= (const BigInteger& number)
	{
		if (this != &number)
		{
			this->arr = number.arr;
			this->sign = number.sign;
		}
		return *this;
	}
	BigInteger BigInteger::operator-()
	{
		if (*this != 0)
			sign = !sign;
		return *this;
	}

	BigInteger::operator std::string() const
	{
		return Get_String_Representation();
	}
	BigInteger::operator long long() const
	{
		return std::stoll(std::string(*this));
	}

	bool BigInteger::Sign() const { return sign; }
	int BigInteger::size() const
	{
		return arr.size();
	}

	std::string BigInteger::Get_String_Representation() const
	{
		std::string str = "";

		if (sign == 0)
			str += "-";

		// Добавить последний элемент без дополнения нулями (число записанно в массив в обратном порядке)
		str += std::to_string(arr[arr.size() - 1]);
		// Добавить последующие элементы дополнив каждый нулями
		for (int i = arr.size() - 2; i >= 0; i--)
		{
			std::string temp = std::to_string(arr[i]);
			while (temp.length() != digit_per_element_of_array && i != arr.size() - 1)
				temp = "0" + temp;
			str += temp;
		}
		return str;
	}
	std::wstring BigInteger::Get_Wstring_Representation() const
	{
		std::wstring str = L"";

		if (sign == 0)
			str += L"-";

		// Добавить последний элемент без дополнения нулями (число записанно в массив в обратном порядке)
		str += std::to_wstring(arr[arr.size() - 1]);
		// Добавить последующие элементы дополнив каждый нулями
		for (int i = arr.size() - 2; i >= 0; i--)
		{
			std::wstring temp = std::to_wstring(arr[i]);
			while (temp.length() != digit_per_element_of_array && i != arr.size() - 1)
				temp = L"0" + temp;
			str += temp;
		}
		return str;
	}
	//End of public functions-------------------------------------------------------------------------


	void BigInteger::SetArray(std::string& str)
	{
		SetSign(str);

		int _size = str.length() / digit_per_element_of_array
			+ (str.length() % digit_per_element_of_array == 0 ? 0 : 1); // Округление вверх
		arr = std::vector<type>(_size);

		//Выборка по digit_per_element_of_array символов
		for (int i = 0, j = str.length(); i < size(); i++, j -= digit_per_element_of_array)
		{
			std::string temp = "";

			if (j <= digit_per_element_of_array)
				temp = str.substr(0, j);
			else
			{
				temp = str.substr(j - digit_per_element_of_array, digit_per_element_of_array);
			}

			arr[i] = std::stol(temp);
		}
	}
	void BigInteger::SetArray(const long long number)
	{
		std::string str = std::to_string(number);
		SetArray(str);
	}
	void BigInteger::SetArray(const std::string& str)
	{
		std::string temp = str;
		SetArray(temp);
	}

	void BigInteger::SetSign(std::string& str)
	{
		if (str[0] == '+')
		{
			sign = 1;
			str.erase(0, 1);
		}
		else
		{
			if (str[0] == '-')
			{
				sign = 0;
				str.erase(0, 1);
			}
		}
	}

	/// <summary>
	/// Определяет какое из двух чисел больше по абсолютной величине
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns>2 Если числа равны, 1 если первое больше, 0 если второе больше</returns>
	int  BigInteger::is_greater(const BigInteger& a, const  BigInteger& b)
	{
		if (a.size() > b.size())
			return 1;
		else
		{
			if (b.size() > a.size())
				return 0;
			else
			{
				for (int i = a.size() -1; i >= 0; i--)
					if (a[i] > b[i])
						return 1;
					else
					{
						if (a[i] < b[i])
							return 0;
					}
				return 2;
			}
		}
	}
	int  BigInteger::is_greater(const BigInteger& a, const  std::string& b)
	{
		if (a.size() > b.size())
			return 1;
		else
		{
			if (b.size() > a.size())
				return 0;
			else
			{
				for (int i = a.size() - 1; i >= 0; i--)
					if (a[i] > b[i])
						return 1;
					else
					{
						if (a[i] < b[i])
							return 0;
					}
				return 2;
			}
		}
	}

	BigInteger BigInteger::Sub(const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger a = first_number;
		int carry = 0;
		for (int i = 0, j = 0; j < second_number.size(); j++, i++)
		{
			if (a[i] >= (second_number[j] + carry))
			{
				a[i] -= (second_number[j] + carry);
				carry = 0;
			}
			else
			{
				a[i] = (a[i] + base) - (second_number[j] + carry);
				carry = 1;
			}
		}
		if (carry == 1)
		{
			for (int i = second_number.size(); i < a.size(); i++)
			{
				if (a[i] == 0)
					a[i] = base - 1;
				else
				{
					a[i]--;
					break;
				}
				
			}
		}
		
		//Удаление ведущих нулей
		while (a.arr[a.size() - 1] == 0 && a.size() > 1)
		{
			
			a.arr.erase(a.arr.end() - 1);
		}
		
		return a;
	}
	BigInteger BigInteger::Add(const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger a = first_number;
		int carry = 0;
		for (int i = 0; i < first_number.size(); i++)
		{
			if (i < second_number.size())
				a[i] = a[i] + second_number[i] + carry;
			else
				a[i] = a[i] + carry;
			if (a[i] > (base - 1))
			{
				carry = 1;
				a[i] %= base;
			}
			else
				carry = 0;
		}
		if (carry == 1)
		{
			a[a.size() - 1] %= base;
			a.arr.push_back(1);
		}
		return a;
	}
	BigInteger BigInteger::Mul(const BigInteger& first_number, const BigInteger& second_number)
	{
		vocmplx fa(first_number.arr.begin(), first_number.arr.end()), fb(second_number.arr.begin(), second_number.arr.end());

		size_t n = 1;
		while (n < std::max(first_number.size(), second_number.size()))  n <<= 1;
		n <<= 1;

		fa.resize(n,0), fb.resize(n,0);

		fa = FFT::FFT_(fa);
		fb = FFT::FFT_(fb);

		for (size_t i = 0; i < n; ++i)
			fa[i] *= fb[i];

		fa = FFT::RFFT_(fa);

		//while ((type)fa[fa.size() - 1].real() == 0)
			//fa.erase(fa.end() - 1);

		std::vector<type> res (n);
		for (size_t i = 0; i < n; ++i)
			res[i] = type(fa[i].real() + 0.5);
		
		int carry = 0;
		for (size_t i = 0; i < n; ++i) {
			res[i] += carry;
			carry = res[i] / base;
			res[i] %= base;
		}

		while ((type)res[res.size() - 1] == 0)
			res.erase(res.end() - 1);

		BigInteger result;
		result.arr = res;
		return result;

	}

	BigInteger BigInteger::Sub(const BigInteger& first_number, const type second_number)
	{
		BigInteger a = first_number;
		int carry = 0;
		if (a[0] >= (second_number + carry))
		{
			a[0] -= (second_number + carry);
			carry = 0;
		}
		else
		{
			a[0] = (a[0] + base) - (second_number + carry);
			carry = 1;
		}
		if (carry == 1)
		{
			for (int i  = 1; i < a.size(); i++)
			{
				if (a[i] == 0)
					a[i] = base - 1;
				else
				{
					a[i]--;
					break;
				}
			}
		}

		//Удаление ведущих нулей
		while (a.arr[a.size() - 1] == 0 && a.size() > 1)
		{

			a.arr.erase(a.arr.end() - 1);
		}

		return a;
	}
	BigInteger BigInteger::Add(const BigInteger& first_number, const type second_number)
	{
		BigInteger a = first_number;
		int carry = 0;
		for (int i = 0; i < first_number.size(); i++)
		{
			if (i < 1)
				a[i] = a[i] + second_number + carry;
			else
				a[i] = a[i] + carry;
			if (a[i] > (base - 1))
			{
				carry = 1;
				a[i] %= base;
			}
			else
				carry = 0;
		}
		if (carry == 1)
		{
			a[a.size() - 1] %= base;
			a.arr.push_back(1);
		}
		return a;
	}
	BigInteger BigInteger::Mul(const BigInteger& first_number, const type second_number)
	{
		BigInteger result = first_number;
		int carry = 0;
		for (size_t i = 0; i < result.size() || carry; ++i) {
			if (i == result.size())
				result.arr.push_back(0);
			long long cur = carry + result[i] * 1ll * second_number;
			result[i] = int(cur % base);
			carry = int(cur / base);
		}
		while (result.size() > 1 && result.arr.back() == 0)
			result.arr.pop_back();
		return result;
	}
}