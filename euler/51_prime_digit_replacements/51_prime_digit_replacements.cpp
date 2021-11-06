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


// https://projecteuler.net/problem=51        Primes primes(limit);
        float ratio = primes.get_num_primes() * 1.0f / limit;
        std::cout << "Number of primes below: " << limit << " is " << primes.get_num_primes() << " ratio: " << ratio << '\n';


#include <cassert>
#include <vector>
#include <cstdint>
#include <iostream>
#include <primes/primes.h>

int main(int argc, char* argv[])
{
    Primes::self_test();
    const uint32_t limit = 10000000;
    Primes primes(limit);
    float ratio = primes.get_num_primes() * 1.0f / limit;
    std::cout << "Number of primes below: " << limit << " is " << primes.get_num_primes() << " ratio: " << ratio << '\n';
    return 0;
}
