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


// https://projecteuler.net/problem=31

#include <iostream>
#include <cassert>

const int coin_count = 8;
const int coin_values[coin_count] = {
    200, 100, 50, 20, 10, 5, 2, 1
};

// returns number of coin sets that sum up to `sum` and contain coin
// with values of `coin_values[min_coin_idx]` or lower
long int coin_sets(int sum, const size_t min_coin_idx)
{
    assert(min_coin_idx < coin_count);
    assert(sum >= 0);
    if (1 >= sum || min_coin_idx == coin_count - 1)
    {
        return 1;
    }
    // find the highest coin value that is smaller than sum
    size_t coin_idx = min_coin_idx;
    while (sum < coin_values[coin_idx])
    {
        coin_idx++;
    }
    assert(coin_idx < coin_count);
    assert(sum >= coin_values[coin_idx]);
    int highest_coin = coin_values[coin_idx];
    // count all sets by enumerating all multiplies of highest coin fitting into sum
    long int sets_counter = 0;
    while (sum >= 0)
    {
        // take highest coin and count the rest with lower coins
        sets_counter += coin_sets(sum, coin_idx + 1);
        sum -= highest_coin;
    }
    return sets_counter;
}

int main()
{
    std::cout << "result: " << coin_sets(200, 0) << '\n';
    return 0;
}
