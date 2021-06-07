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

#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "FFT.h"

namespace leart
{
    class BigInteger
    {
        using type = unsigned long long; // Type of elements of array

        static const type base = 1'000'000'000; // Max value of each element of array
        static const short digit_per_element_of_array = 9; // log10 (base)

    public:
        BigInteger();
        BigInteger(const long long integer_representation_of_number);
        BigInteger(const std::string& string_representation_of_number);
        //BigInteger(const char* string_representation_of_number);
        BigInteger(const BigInteger& object_to_copy); // Copy constructor

    public:
        type& operator[] (const int index);
        type operator[] (const int index) const;

    public:
        friend std::ostream& operator<<(std::ostream& output, const BigInteger& number);
        friend std::istream& operator>>(std::istream& input, BigInteger& number);

    public:
        friend BigInteger operator- (const BigInteger& first_number, const BigInteger& second_number); // Logic only
        friend BigInteger operator+ (const BigInteger& first_number, const BigInteger& second_number); // Logic only
        friend BigInteger operator* (const BigInteger& first_number, const BigInteger& second_number); // Logic only

        friend BigInteger operator+ (const BigInteger& first_number, const long long second_number); // Logic only
        friend BigInteger operator- (const BigInteger& first_number, const long long second_number); // Logic only
        friend BigInteger operator* (const BigInteger& first_number, const long long second_number); // Logic only

        friend BigInteger operator* (const long long first_number, const BigInteger& second_number); // Logic only

        BigInteger& operator++ (); // Prefix Increment
        BigInteger& operator++ (int); // Postfix Increment

        BigInteger& operator-- (); // Prefix Decrement
        BigInteger& operator-- (int); // Postfix Decrement

        void operator+= (const BigInteger& number);
        void operator+= (const long long number);

        void operator-= (const BigInteger& number);
        void operator-= (const long long number);

        //TODO:Don't forget about these methods up here
        
        //TODO:Redo all comparsion operators (Now we have signed BigInteger)
    public:
        friend bool operator== (const BigInteger& first_number, const BigInteger& second_number);
        friend bool operator!= (const BigInteger& first_number, const BigInteger& second_number);
        friend bool operator< (const BigInteger& first_number, const BigInteger& second_number);
        friend bool operator<= (const BigInteger& first_number, const BigInteger& second_number);
        friend bool operator> (const BigInteger& first_number, const BigInteger& second_number);
        friend bool operator>= (const BigInteger& first_number, const BigInteger& second_number);
    
    public:
        BigInteger& operator= (const BigInteger& object_to_assign);
        BigInteger operator-(); // Sign changer

    public:
        explicit operator long long() const;
        explicit operator std::string() const;

    public:
        bool Sign() const;
        std::string Get_String_Representation() const;
        std::wstring Get_Wstring_Representation() const;

    private:
        int size() const;

    public:
        void SetArray(std::string& string_representation_of_number);
        void SetArray(const long long integer_representation_of_number);
        void SetArray(const std::string& string_representation_of_number);
        /// <summary>
        /// ”станавливает знак удал¤¤ его из исходной строки
        /// </summary>
        /// <param name="string_representation_of_number"></param>
        void SetSign(std::string& string_representation_of_number);

        /// <summary>
        /// ќпредел¤ет наибольше из двух чисел
        /// </summary>
        /// <param name="first_number">ѕервое число</param>
        /// <param name="second_number">¬торое число</param>
        /// <returns>¬озваращает 1 если первое число больше, 0 если второе число больше, 2 если числа равны</returns>
        static int  is_greater(const BigInteger& first_number, const  BigInteger& second_number);
        static int  is_greater(const BigInteger& first_number, const  std::string& second_number);

        static BigInteger Sub(const BigInteger& first_number, const BigInteger& second_number);
        static BigInteger Add(const BigInteger& first_number, const BigInteger& second_number);
        static BigInteger Mul(const BigInteger& first_number, const BigInteger& second_number);

        //TODO:Implement short Sub, Add, Mul
        static BigInteger Sub(const BigInteger& first_number, const type second_number); // Only when second number < base
        static BigInteger Add(const BigInteger& first_number, const type second_number); // Only when second number < base
        static BigInteger Mul(const BigInteger& first_number, const type second_number); // Only when second number < base

    private:
        std::vector<type> arr;
        bool sign = 1;
    };
}