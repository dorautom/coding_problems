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


// https://projecteuler.net/problem=50

#include <cassert>
#include <cstdint>
#include <iostream>
#include <primes/primes.h>

class PrimesSums
{
public:
    PrimesSums(uint32_t limit) : primes_(limit), max_prime_sum_(0), max_counter_(0)
    {
        assert(limit > 5);
        calculate();
        assert(primes_.is_prime(max_prime_sum_));
    }

    uint32_t get_max_prime_sum() const
    {
        return max_prime_sum_;
    }

    uint32_t get_max_counter() const
    {
        return max_counter_;
    }

    static void self_test()
    {
        PrimesSums test(100);
        assert(test.prime_sum_in_range(2, 14) == 41);
        assert(test.get_max_prime_sum() == 41);
        std::cout << "PrimesSums self test OK\n";
    }

protected:
    void calculate()
    {
        uint32_t start = 2;
        max_prime_sum_ = 0;
        max_counter_ = 0;
        while (start)
        {
            uint64_t sum = start;
            uint32_t counter = 1;
            uint32_t end = primes_.get_next_prime(start);
            while (end)
            {
                sum += end;
                counter++;
                end = primes_.get_next_prime(end);
                if (sum >= primes_.get_limit())
                    break;
                if (primes_.is_prime(sum) && counter > max_counter_)
                {
                    max_counter_ = counter;
                    max_prime_sum_ = sum;
                }
            }
            assert(end == 0 || prime_sum_in_range(start, end) == sum);
            start = primes_.get_next_prime(start);
        }
    }

    uint64_t prime_sum_in_range(uint32_t min, uint32_t max)
    {
        assert(min < primes_.get_limit() && max < primes_.get_limit());
        assert(min <= max);
        uint64_t sum = 0;
        for (uint32_t num = min; num < max; num++)
        {
            if (primes_.is_prime(num)) 
                sum += num;
        }  
        return sum;
    }

    Primes primes_;
    uint32_t max_prime_sum_;
    uint32_t max_counter_;
};

int main(int argc, char* argv[])
{
    Primes::self_test();
    PrimesSums::self_test();
    uint32_t limit = 1000; // default
    if (argc > 1)
    {
        long int value = std::atol(argv[1]);
        assert(value > 0);
        limit = static_cast<uint32_t>(value);
    }
    std::cout << "Limit is " << limit << '\n';
    PrimesSums sums(limit);
    std::cout << "Result: " << sums.get_max_prime_sum() << " is sum of " << sums.get_max_counter() << " consecutive primes" << '\n';
    return 0;
}
