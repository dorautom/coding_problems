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
#include <iostream>
#include <primes/primes.h>
#include <combinatorial/ordered.h>
#include <numerical/digit.h>
#include <io/container.h>

// returns histogram of digits in a number
std::vector<int> count_digits(std::string number);

/// finds positions of given digit in a number
std::vector<Pos> get_positions(const std::string& number, const Digit& digit);

/// replaces digits at given positions in a number with the digit given as an argument
void replace_digits(std::string& number, const Digit& digit, const std::vector<Pos>& positions);

/// returns a family of primes generated from a number by replacing digits at given positions with each one digit
/// the numbers are sorted in ascending order
std::vector<uint64_t> check_primes_family(const std::string& number, const std::vector<Pos>& positions);

/// returns first family of primes in range [left, right) with repeating digit, 
/// given number of repeated digits and minimal family size, updates left border ot range,
/// so it can be run iteratively
std::vector<uint64_t> get_family(uint64_t& left, uint64_t right, uint8_t repeats, int8_t family_size);


int main(int argc, char* argv[])
{
    const std::vector<uint64_t> family_6 = {13, 23, 43, 53, 73, 83};
    const std::vector<uint64_t> family_7 = {56003, 56113, 56333, 56443, 56663, 56773, 56993};
    uint64_t start = 1;
    assert(get_family(start, 100000000, 2, 6) == family_6);
    std::cout << "Now starting from " << start << '\n';
    assert(get_family(start, 100000000, 2, 7) == family_7);
    std::cout << "Now starting from " << start << '\n';
    std::cout << get_family(start, 100000000, 3, 8) << '\n';
    return 0;
}
