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

/* problem: A child is running up a staircase with n steps and can hop either 1, 2 or 3 steps at a time.
            Implement a method to count how many possible ways the child can run up the stairs
*/

#include <cassert>
#include <vector>
#include <iostream>

long int steps(int n, std::vector<long int>& memo)
{
    if (n < 0) return 0;
    if (n == 0) return 1;
    if (memo[n] != -1)
    {
        return memo[n];
    }
    long int result = steps(n-1, memo) + steps(n-2, memo) + steps(n-3, memo);
    memo[n] = result;
    return result;
}

long int count_ways(int n)
{
    assert(n > 0);
    std::vector<long int> memo(n+1, -1);
    return steps(n, memo);
}

int main(int argc, char** argv)
{
    std::cout << count_ways(2) << '\n';
    std::cout << count_ways(3) << '\n';
    std::cout << count_ways(37) << '\n';
    assert(count_ways(1) == 1);
    assert(count_ways(2) == 2);
    assert(count_ways(3) == 4);
    return 0;
}
