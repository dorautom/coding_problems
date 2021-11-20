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

#include <list>
#include <cassert>

namespace combinatorial
{

/// recursive template function for generating all combinations of given size from
/// a list of elements, initial order of elements is not changed
template <typename T>
std::list<std::list<T> > generate_ordered_combinations(const std::list<T>& input, int size)
{
    std::list<std::list<T> > result;
    // base case
    if (size <= 0 || size > input.size())
    {
        // create list with one empty combination as null output
        return std::list<std::list<T>>(1);
    }
    if (size == input.size())
    {
        result.push_back(input);
        return result;
    }
    // recursive case
    std::list<T> tail = input;
    T head = tail.front();
    tail.pop_front();
    result.splice(result.end(), generate_ordered_combinations(tail, size));
    std::list<std::list<T> > with_head;
    for (auto& comb : generate_ordered_combinations(tail, size - 1))
    {
        comb.push_front(head);
        result.push_back(comb);
    }
    for (auto& comb : result)
    {
        assert(comb.size() == size);
    }
    return result;
}

namespace testing
{

void test_generate_ordered_combinations()
{
    std::list<int> input_1 = {1};
    std::list<int> input_2 = {2, 3};
    std::list<int> input_3 = {1, 2, 3};
    std::list<int> input_4 = {1, 2, 3, 4};
    std::list<std::list<int>> null_output = {{}};
    std::list<std::list<int>> output_1 = {{1}};
    std::list<std::list<int>> output_2 = {{3}, {2}};
    std::list<std::list<int>> output_3 = {{2,3}, {1,3}, {1,2}};
    std::list<std::list<int>> output_4 = {{3,4}, {2,4}, {2,3}, {1,4}, {1,3}, {1,2}};
    assert(generate_ordered_combinations(input_1, 0) == null_output);
    assert(generate_ordered_combinations(input_1, 1) == output_1);
    assert(generate_ordered_combinations(input_2, 1) == output_2);
    assert(generate_ordered_combinations(input_3, 2) == output_3);
    assert(generate_ordered_combinations(input_4, 2) == output_4);
}

}

}
