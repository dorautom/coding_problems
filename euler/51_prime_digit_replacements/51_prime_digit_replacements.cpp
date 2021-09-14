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


// https://projecteuler.net/problem=51

#include <cassert>
#include <vector>
#include <cstdint>
#include <iostream>
#include <primes/primes.h>

class PrimesFamily
{
public:
    PrimesFamily(uint32_t limit, uin32_t digits) : limit_(limit), digits_(digits), min_prime_(0), primes_(limit_)
    {
        assert(limit_ > 1);
        assert(digits_ > 1);
    }

    const std::vector<uint32_t>& get_family() const
    {
        return family_;
    }

    uint32_t get_min_prime() const
    {
        return min_prime_;
    }

    void find_smallest_family(uint32_t bottom_limit, int family_count)
    {
        // go through primes with repeating digits, check if primes after replacement
        // mark checked primes?
    }

private:
    // find biggest family
    void calculate()
    {

    }

    uint32_t limit_;
    uint32_t min_prime_;
    std::vector<uint32_t> family_;
    Primes primes_;
};

int main(int argc, char* argv[])
{
    Primes::self_test();
    PrimesFamily family(1000000, 3);
    family.find_smallest_family(8);
    std::cout << "Result: " << family.get_min_prime() << " consists of: ";
    for (auto p : family.get_family())
        std::cout << p << ' ';
    std::cout << '\n';
    return 0;
}
