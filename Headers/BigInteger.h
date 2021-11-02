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
#include <type_traits>
#include "../Headers/FFT.h"

namespace leart
{
    template <typename Type, std::enable_if_t<std::is_integral<Type>::value, bool> = true>
    inline constexpr unsigned short log10(Type number)
    {
        unsigned short result = 1;
        while ((number /= 10) != 0)
            result++;
        return result;
    }
    class BigInteger
    {
        using type = unsigned long long; // Type of elements of array

        static const type base = 1'000'000'000; // Max value of each element of array 
        static constexpr short digit_per_element_of_array = leart::log10(base);

    public:
        BigInteger();
        template<typename Type, std::enable_if_t<std::is_integral<Type>::value, bool> = true>
        inline BigInteger(const Type integer_representation_of_number)
        {
            SetArray(integer_representation_of_number);
        }
        BigInteger(const std::string& string_representation_of_number);
        BigInteger(const char* const string_representation_of_number);
        BigInteger(const BigInteger& object_to_copy);

    private:
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
        BigInteger operator++ (int); // Postfix Increment

        BigInteger& operator-- (); // Prefix Decrement
        BigInteger operator-- (int); // Postfix Decrement

        const BigInteger& operator+= (const BigInteger& number);
        const BigInteger& operator+= (const long long number);

        const BigInteger& operator-= (const BigInteger& number);
        const BigInteger& operator-= (const long long number);

        //TODO:Don't forget about these methods up here
        
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
        void SetSign(std::string& string_representation_of_number);

        static int  is_greater(const BigInteger& first_number, const  BigInteger& second_number);
        static int  is_greater(const BigInteger& first_number, const  std::string& second_number);

        static BigInteger Sub(const BigInteger& first_number, const BigInteger& second_number);
        static BigInteger Add(const BigInteger& first_number, const BigInteger& second_number);
        static BigInteger Mul(const BigInteger& first_number, const BigInteger& second_number);

        static BigInteger Sub(const BigInteger& first_number, const type second_number); // Only when second number < base
        static BigInteger Add(const BigInteger& first_number, const type second_number); // Only when second number < base
        static BigInteger Mul(const BigInteger& first_number, const type second_number); // Only when second number < base

        BigInteger& Inc(BigInteger& number);
        BigInteger& Dec(BigInteger& number);

    private:
        std::vector<type> arr;
        bool sign = 1;
    };
}