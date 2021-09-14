// MIT License

// Copyright (c) 2021 Tomasz Dorau https://github.com/dorautom/

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.


#pragma once

#include <cassert>
#include <vector>
#include <iostream>
#include "primes.h"

class Primes
{
public:
    Primes(uint32_t limit) : limit_(limit), is_prime_(limit_, 1)
    {
        is_prime_[0] = is_prime_[1] = 0; 
        for (int i = 2; i < limit_ / 2 + 1; i++)
        {
            if (is_prime_[i])
            {
                for (int j = 2*i; j < limit_; j += i )
                {
                    is_prime_[j] = 0;
                }
            }
        }
    }

    bool is_prime(uint32_t number) const
    {
        assert(number < limit_);
        return is_prime_.at(number);
    }

    static void self_test()
    {
        Primes range(10);
        assert(range.is_prime(2));
        assert(range.is_prime(3));
        assert(!range.is_prime(4));
        assert(range.is_prime(5));
        assert(!range.is_prime(6));
        assert(range.is_prime(7));
        assert(!range.is_prime(8));
        assert(!range.is_prime(9));
        assert(range.get_next_prime(5) == 7);
        std::cout << "Primes self test OK\n";
    }

    uint32_t get_limit() const
    {
        return limit_;
    }

    uint32_t get_next_prime(uint32_t num)
    {
        assert(num < limit_);
        do
        {
            num++;
        } while (num < limit_ && !is_prime_.at(num));
        return num < limit_ ? num : 0;
    }

private:
    uint32_t limit_;
    std::vector<uint8_t> is_prime_;
};
