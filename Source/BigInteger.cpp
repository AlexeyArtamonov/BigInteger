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

#include "../Headers/BigInteger.h"

namespace leart
{
	BigInteger::BigInteger()
	{
		SetArray("0");
	}
	BigInteger::BigInteger(const std::string& s_number)
	{
		SetArray(s_number);
	}
	BigInteger::BigInteger(const char*		  s_number)
	{
		SetArray(s_number);
	}
	BigInteger::BigInteger(const BigInteger&  copy)
	{
		_sign = copy._sign;
		arr = copy.arr;
	}

	BigInteger::type& BigInteger::operator[] (const int index)
	{
		return arr[index];
	}
	const BigInteger::type& BigInteger::operator[] (const int index) const
	{
		return arr[index];
	}

	std::istream& operator>>(std::istream& input, BigInteger& number)
	{
		std::string temp;
		input >> temp;
		number.SetArray(temp);
		return input;
	}
	std::ostream& operator<<(std::ostream& output, const BigInteger& number)
	{
		return (output << number.getString());
	}

	#pragma region Arithmetic operators
	const BigInteger operator+ (const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger result;

		const int BIcmp = BigInteger::BigIntegerCompare(first_number, second_number);
		if (first_number._sign == BigInteger::Sign::plus  && second_number._sign == BigInteger::Sign::plus)
		{
			if (first_number.size() >= second_number.size())
				result = BigInteger::Add(first_number, second_number);
			else
				result = BigInteger::Add(second_number, first_number);

			result._sign = BigInteger::Sign::plus;
		}
		else if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::minus)
		{
			if (BIcmp == 0)
			{
				result.SetArray(0);
				result._sign = BigInteger::Sign::plus;
			}
			else if (BIcmp == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result._sign = BigInteger::Sign::plus;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result._sign = BigInteger::Sign::minus;
			}
		}
		else if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
		{
			if (BIcmp == 0)
			{
				result.SetArray(0);
				result._sign = BigInteger::Sign::plus;
			}
			else if (BIcmp == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result._sign = BigInteger::Sign::minus;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result._sign = BigInteger::Sign::plus;
			}
		}
		else
		{
			if (first_number.size() > second_number.size())
				result = BigInteger::Add(first_number, second_number);
			else
				result = BigInteger::Add(second_number, first_number);
			result._sign = BigInteger::Sign::minus;
		}

		return result;
	}
	const BigInteger operator- (const BigInteger& first_number, const BigInteger& second_number)
	{
		BigInteger result;

		const int BIcmp = BigInteger::BigIntegerCompare(first_number, second_number);
		if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::plus)
		{
			if (BIcmp == 0)
			{
				result.SetArray(0);
				result._sign = BigInteger::Sign::plus;
			}
			else if (BIcmp == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result._sign = BigInteger::Sign::plus;
			}
			else
			{
				result = BigInteger::Sub(second_number,first_number);
				result._sign = BigInteger::Sign::minus;
			}
		}
		else if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
		{

			if (BIcmp == 1)
			{
				result = BigInteger::Add(first_number, second_number);
				result._sign = BigInteger::Sign::minus;
			}
			else
			{
				result = BigInteger::Add(second_number, first_number);
				result._sign = BigInteger::Sign::minus;
			}
		}
		else if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::minus)
		{
			if (BIcmp == 1)
			{
				result = BigInteger::Add(first_number, second_number);
				result._sign = BigInteger::Sign::plus;
			}
			else
			{
				result = BigInteger::Add(second_number, first_number);
				result._sign = BigInteger::Sign::plus;
			}
		}
		else
		{
			if (BIcmp == 0)
			{
				result.SetArray(0);
				result._sign = BigInteger::Sign::plus;
			}
			else if (BIcmp == 1)
			{
				result = BigInteger::Sub(first_number, second_number);
				result._sign = BigInteger::Sign::minus;
			}
			else
			{
				result = BigInteger::Sub(second_number, first_number);
				result._sign = BigInteger::Sign::plus;
			}
		}

		return result;

	}
	const BigInteger operator* (const BigInteger& first_number, const BigInteger& second_number)
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
				result._sign = (BigInteger::Sign)!((bool)first_number._sign ^ (bool)second_number._sign);
				return result;
			}
		}
		
	}

	const BigInteger operator+ (const BigInteger& first_number, const long long second_number)
	{
		if (second_number < 0)
			return operator-(first_number, -second_number);

		if (second_number > BigInteger::base)
			return operator+ (first_number, (BigInteger)second_number);

		return BigInteger::Add(first_number, second_number);
	}
	const BigInteger operator- (const BigInteger& first_number, const long long second_number)
	{
		if (second_number < 0)
			return operator+(first_number, -second_number);

		BigInteger result;

		if (first_number.size() > 1)
		{
			result = BigInteger::Sub(first_number, second_number);
			result._sign = BigInteger::Sign::plus;
		}
		else
		{
			if (second_number < BigInteger::base)
			{
				if (first_number[0] > second_number)
				{
					result = BigInteger::Sub(first_number, second_number);
					result._sign = BigInteger::Sign::plus;
				}
				else
				{
					result = BigInteger::Sub((BigInteger)second_number, first_number);
					result._sign = BigInteger::Sign::minus;
				}
			}
			else
				result = operator- (first_number, (BigInteger)second_number);
		}
		return result;
	}
	const BigInteger operator* (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base)
			return operator*(first_number, (BigInteger)second_number);

		BigInteger result = BigInteger::Mul(first_number,second_number);
		result._sign = (BigInteger::Sign)!((bool)first_number._sign ^ (second_number >= 0? 1 : 0));
		return result;
	}
	const BigInteger operator* (const long long first_number, const BigInteger& second_number)
	{
		return operator* (second_number, first_number);
	}

	// Prefix Increment
	BigInteger& BigInteger::operator++ ()
	{
		if (_sign == BigInteger::Sign::minus)
			return Dec(*this);
		else
			return Inc(*this);
	}
	// Postfix Increment
	BigInteger  BigInteger::operator++ (int) 
	{
		BigInteger old = *this;
		++(*this);
		return old;
	}

	// Prefix Decrement
	BigInteger& BigInteger::operator-- ()
	{
		if (_sign == BigInteger::Sign::minus)
			return Inc(*this);
		else
			return Dec(*this);
	}
	// Postfix Decrement
	BigInteger  BigInteger::operator-- (int)
	{
		BigInteger old = *this;
		--(*this);
		return old;
		
	}

	const BigInteger& BigInteger::operator+= (const BigInteger& number)
	{
		*this = *this + number;
		return *this;
	}
	const BigInteger& BigInteger::operator+= (const long long   number)
	{
		*this = *this + number;
		return *this;
	}

	const BigInteger& BigInteger::operator-= (const BigInteger& number)
	{
		*this = *this - number;
		return *this;
	}
	const BigInteger& BigInteger::operator-= (const long long   number)
	{
		*this = *this - number;
		return *this;
	}

	const BigInteger& BigInteger::operator*= (const BigInteger& number)
	{
		*this = *this * number;
		return *this;
	}
	const BigInteger& BigInteger::operator*= (const long long   number)
	{
		*this = *this * number;
		return *this;
	}
	#pragma endregion

	#pragma region Comparison functions
	bool operator== (const BigInteger& first_number, const BigInteger& second_number)
	{
		return (BigInteger::BigIntegerCompare(first_number, second_number) == 0 && first_number._sign == second_number._sign);
	}
	bool operator!= (const BigInteger& first_number, const BigInteger& second_number)
	{
		return !operator==(first_number, second_number);
	}
	bool operator>  (const BigInteger& first_number, const BigInteger& second_number)
	{
		const int BIcmp = BigInteger::BigIntegerCompare(first_number, second_number);
		switch (BIcmp)
		{
			/*
			* 3	>  5 = false
			*-3 >  5 = false
			* 3	> -5 = true
			*-3	> -5 = true
			*/
			case -1:
			{
					 if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::plus)
					return false;
				else if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
					return false;
				else
					return true;
				break;
			}
			/*
			* 3	> -3 = true
			*-3 >  3 = false
			* 3	>  3 = false
			*-3	> -3 = false
			*/
			case 0:
			{
				if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::minus)
					return true;
				else
					return false;
			}
			/*
			*-5	> -3 = false
			*-5 >  3 = false
			* 5	>  3 = true
			* 5	> -3 = true
			*/
			case 1:
			{
					 if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::minus)
					return false;
				else if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
					return false;
				else
					return true;

				break;
			}
		}
	
	}
	bool operator<  (const BigInteger& first_number, const BigInteger& second_number)
	{
		const int BIcmp = BigInteger::BigIntegerCompare(first_number, second_number);
		switch (BIcmp)
		{
			/*
			* 3	<  5 = true
			*-3 <  5 = true
			* 3	< -5 = false
			*-3	< -5 = false
			*/
			case -1:
			{
					 if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::plus)
					return true;
				else if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
					return true;
				else
					return false;
			}
			/*
			*-3 <  3 = true
			* 3	<  3 = false
			* 3	< -3 = false
			*-3	< -3 = false
			*/
			case 0:
			{
				if (first_number._sign == BigInteger::Sign::minus && second_number._sign == BigInteger::Sign::plus)
					return true;
				else
					return false;
			}
			/*
			* 5	<  3 = false
			* 5	< -3 = false
			*-5 <  3 = true
			*-5	< -3 = true
			*/
			case 1:
			{
					 if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::plus)
					return false;
				else if (first_number._sign == BigInteger::Sign::plus && second_number._sign == BigInteger::Sign::minus)
					return false;
				return true;
			}
		}
		
	}
	bool operator>= (const BigInteger& first_number, const BigInteger& second_number)
	{
		return (first_number > second_number || first_number == second_number);
	}
	bool operator<= (const BigInteger& first_number, const BigInteger& second_number)
	{
		return (first_number < second_number || first_number == second_number);
	}

	bool operator== (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator==(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return false;

		return first_number[0] == second_number;
			
	}
	bool operator!= (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator!=(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return true;

		return first_number[0] != second_number;
	}
	bool operator<  (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator<(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return false;
		
		return first_number[0] < second_number;
	}
	bool operator<= (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator<=(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return false;

		return first_number[0] <= second_number;
	}
	bool operator>  (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator>(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return true;

		return first_number[0] > second_number;
	}
	bool operator>= (const BigInteger& first_number, const long long second_number)
	{
		if (second_number >= BigInteger::base || second_number < 0)
			return operator<(first_number, BigInteger(second_number));
		if (first_number.size() > 1)
			return true;

		return first_number[0] >= second_number;
	}

	bool operator== (const long long second_number,  const BigInteger& first_number)
	{
		return operator==(first_number, second_number);
	}
	bool operator!= (const long long second_number,  const BigInteger& first_number)
	{
		return operator!=(first_number, second_number);
	}
	bool operator<  (const long long second_number,  const BigInteger& first_number)
	{
		return operator<(first_number, second_number);
	}
	bool operator<= (const long long second_number,  const BigInteger& first_number)
	{
		return operator<=(first_number, second_number);
	}
	bool operator>  (const long long second_number,  const BigInteger& first_number)
	{
		return operator>(first_number, second_number);
	}
	bool operator>= (const long long second_number,  const BigInteger& first_number)
	{
		return operator>=(first_number, second_number);
	}

	#pragma endregion 

	BigInteger& BigInteger::operator= (const BigInteger& number)
	{
		if (this != &number)
		{
			this->arr = number.arr;
			this->_sign = number._sign;
		}
		return *this;
	}
	BigInteger& BigInteger::operator- ()
	{
		if (*this != 0)
			_sign = BigInteger::OppositeSign(_sign);
		return *this;
	}

	BigInteger::operator std::string() const
	{
		return getString();
	}
	BigInteger::operator long long() const
	{
		return std::stoll(std::string(*this));
	}

	BigInteger::Sign BigInteger::sign() const
	{
		return _sign;
	}
	int BigInteger::size() const
	{
		return arr.size();
	}

	std::string BigInteger::getString() const
	{
		std::string str = "";

		if (_sign == BigInteger::Sign::minus)
			str += "-";

		// Adding first number without leading zeros (number stored in array in reverse order)
		str += std::to_string(arr[arr.size() - 1]);
		// Adding other numbers complementing up to "digits_per_element_of_array" digits
		for (int i = arr.size() - 2; i >= 0; i--)
		{
			std::string temp = std::to_string(arr[i]);
			while (temp.length() != digit_per_element_of_array && i != arr.size() - 1)
			{
				temp = "0" + temp;
			}
			str += temp;
		}
		return str;
	}
	std::wstring BigInteger::getWstring() const
	{
		std::wstring str = L"";

		if (_sign == BigInteger::Sign::minus)
			str += L"-";

		// Adding first number without leading zeros (number stored in array in reverse order)
		str += std::to_wstring(arr[arr.size() - 1]);
		// Adding other numbers complementing up to "digits_per_element_of_array" digits
		for (int i = arr.size() - 2; i >= 0; i--)
		{
			std::wstring temp = std::to_wstring(arr[i]);
			while (temp.length() != digit_per_element_of_array && i != arr.size() - 1)
			{
				temp = L"0" + temp;
			}
			str += temp;
		}
		return str;
	}

	void BigInteger::SetArray(std::string& str)
	{
		SetSign(str);

		int _size = str.length() / digit_per_element_of_array
			+ (str.length() % digit_per_element_of_array == 0 ? 0 : 1); // Round up
		arr = std::vector<type>(_size);

		//Extracting digit_per_element_of_array symbols for each element of array
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

	// Set sign and delete sign from string
	void BigInteger::SetSign(std::string& str)
	{
		if (str[0] == '+')
		{
			_sign = BigInteger::Sign::plus;
			str.erase(0, 1);
		}
		else
		{
			if (str[0] == '-')
			{
				_sign = BigInteger::Sign::minus;
				str.erase(0, 1);
			}
		}
	}

	/// <summary>
	/// Works like strcmp
	/// </summary>
	/// <returns> -1 if first number lesser than second, 0 if they are equal, 1 if first number greater than second</returns>
	int  BigInteger::BigIntegerCompare(const BigInteger& first_number, const  BigInteger& second_number)
	{
		if (first_number.size() > second_number.size())
			return 1;
		else
		{
			if (second_number.size() > first_number.size())
				return -1;
			else
			{
				for (int i = first_number.size() - 1; i >= 0; i--)
				{
					if (first_number[i] > second_number[i])
						return 1;
					else
					{
						if (second_number[i] > first_number[i])
							return -1;
					}
				}
				return 0;
			}
		}
	}

	#pragma region Arithmetic functions
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
		
		//Deleting leading zeros
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
		std::vector<std::complex<double>>
			fa(first_number.arr.begin(), first_number.arr.end()),
			fb(second_number.arr.begin(), second_number.arr.end());

		int n = 1;
		while (n < std::max(first_number.size(), second_number.size()))  n <<= 1;
		n <<= 1;

		fa.resize(n,0), fb.resize(n,0);

		fa = FFT::transform(fa);
		fb = FFT::transform(fb);

		for (int i = 0; i < n; i++)
		{
			fa[i] *= fb[i];
		}

		fa = FFT::reverseTransform(fa);

		std::vector<type> res (n);
		for (int i = 0; i < n; i++)
		{
			double temp = fa[i].real();
			res[i] = type(fa[i].real() + 0.5);
		}
		
		int carry = 0;
		for (int i = 0; i < n; i++) 
		{
			res[i] += carry;
			carry = res[i] / base;
			res[i] %= base;
		}

		while ((type)res[res.size() - 1] == 0)
		{
			res.erase(res.end() - 1);
		}

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
			for (int i = 1; i < a.size(); i++)
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

		//Deleting leading zeros
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
		for (int i = 0; i < result.size() || carry; i++) 
		{
			if (i == result.size())
				result.arr.push_back(0);
			long long cur = carry + result[i] * 1ll * second_number;
			result[i] = int(cur % base);
			carry = int(cur / base);
		}
		while (result.size() > 1 && result.arr.back() == 0)
		{
			result.arr.pop_back();
		}
		return result;
	}

	BigInteger& BigInteger::Inc(BigInteger& number)
	{
		int carry = 0;
		for (int i = 0; i < number.size(); i++)
		{
			if (i < 1)
				number.arr[i] = number.arr[i] + 1 + carry;
			else
				number.arr[i] = number.arr[i] + carry;
			if (number.arr[i] > (base - 1))
			{
				carry = 1;
				number.arr[i] %= base;
			}
			else
				carry = 0;
		}

		if (carry == 1)
		{
			number.arr[size() - 1] %= base;
			number.arr.push_back(1);
		}
		return number;
	}
	BigInteger& BigInteger::Dec(BigInteger& number)
	{
		if (number[0] == 0 && number.size() == 1)
		{
			number[0] = 1;
			number._sign = BigInteger::Sign::minus;
			return number;
		}
		int carry = 0;
		if (number.arr[0] >= 1)
		{
			number.arr[0] -= 1;
			carry = 0;
		}
		else
		{
			number.arr[0] = (number.arr[0] + base) - 1;
			carry = 1;
		}
		if (carry == 1)
		{
			for (int i = 1; i < number.size(); i++)
			{
				if (number.arr[i] == 0)
					number.arr[i] = base - 1;
				else
				{
					number.arr[i]--;
					break;
				}
			}
		}

		//Deleting leading zeros
		while (number.arr[number.size() - 1] == 0 && number.size() > 1)
		{
			number.arr.erase(number.arr.end() - 1);
		}
		if (number.arr[0] == 0 && number._sign == BigInteger::Sign::minus && number.size() == 1)
			number._sign = BigInteger::Sign::plus;
		return number;
	}
	#pragma endregion
}