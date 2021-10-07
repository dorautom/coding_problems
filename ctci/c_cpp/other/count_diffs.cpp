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

#include <iostream>
#include <unordered_map>
#include <tuple>
#include <vector>
#include <list>

typedef std::tuple<int, int> pair_t;
typedef std::list<pair_t> pair_list_t;

pair_list_t find_pairs(std::vector<int>& tab, int diff)
{
    std::unordered_map<int, bool> set;
    pair_list_t pairs;

    for (auto value : tab)
    {
        set[value] = true;
    }
    for (auto value : tab)
    {
        if (set.find(value + diff) != set.end())
        {
            pairs.emplace_back(std::make_tuple(value, value + diff));
        }
    }
    return pairs;
}


int main()
{
    std::vector<int> example = { 1, 7, 5, 9, 2, 12, 3 };
    pair_list_t pairs = find_pairs(example, 2);
    for (auto pair : pairs)
    {
        std::cout << '(' << std::get<0>(pair) << ',' << std::get<1>(pair) << "),";
    }
    std::cout << '\n';
    return 0;
}
