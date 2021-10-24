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

// problem: sum two decimal numbers represented by linked lists of digits, return result as a linked list of digits
// 1. solve the problem if number are stored in reverse order: (7 -> 1 -> 6) + (5 -> 9 -> 2) <=> 617 + 295
// 2. solve the problem if number are stored in forward order: (6 -> 1 -> 7) + (2 -> 9 -> 5) <=> 617 + 295

#include <forward_list>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>

namespace digits_reverse_order
{

class SumCalculator
{

    const std::forward_list<int>& list1_;
    const std::forward_list<int>& list2_;
    std::forward_list<int>::const_iterator tail_;

    bool add_digits(std::forward_list<int>& out, std::forward_list<int>::const_iterator& in_it1, std::forward_list<int>::const_iterator& in_it2, int& rest)
    {
        assert(rest < 10 && rest >= 0);
        if (in_it1 == list1_.end() && in_it2 == list2_.end() && rest == 0)
            return false;
        if (in_it1 != list1_.end())
        {
            rest += *in_it1;
            in_it1++;
        }
        if (in_it2 != list2_.end())
        {
            rest += *in_it2;
            in_it2++;
        }
        if (rest >= 10)
        {
            out.insert_after(tail_, rest % 10);
            tail_++;
            rest = rest / 10;
        }
        else
        {
            out.insert_after(tail_, rest);
            tail_++;
            rest = 0;
        }
        return true;
    }

public:

    SumCalculator(const std::forward_list<int>& l1, const std::forward_list<int>& l2) : list1_(l1), list2_(l2)
    {  
    }

    std::forward_list<int> operator()()
    {
        int rest = 0;
        std::forward_list<int> sum;
        auto it1 = list1_.cbegin();
        auto it2 = list2_.cbegin();
        tail_ = sum.cbefore_begin();
        while (add_digits(sum, it1, it2, rest));
        return sum;
    }

};

std::forward_list<int> sum_lists(const std::forward_list<int>& l1, const std::forward_list<int>& l2)
{
    SumCalculator summer(l1, l2);
    return summer();
}

}

namespace digits_forward_order
{

std::forward_list<int> sum_lists(const std::forward_list<int>& l1, const std::forward_list<int>& l2);

}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::forward_list<T>& l)
{
    size_t size = 0;
    std::for_each(l.begin(), l.end(), [&](const T& item){ os << item << ' '; size++; });
    os << "[" << size << "]" << '\n';
    return os;
}

using fwd_list_bin_operand = std::forward_list<int>(const std::forward_list<int>&, const std::forward_list<int>&);

bool verify(const std::forward_list<int>& in1, const std::forward_list<int>& in2, const std::forward_list<int>& out_ref, 
            std::function<std::forward_list<int>(const std::forward_list<int>&, const std::forward_list<int>&)> tested_fun)
{
    auto result = tested_fun(in1, in2);
    std::cout << result;
    return result == out_ref;
}

int main()
{
    assert(verify({8, 7, 9}, {5, 8, 6}, {3, 6, 6, 1}, digits_reverse_order::sum_lists));
//    ref = {1, 6, 6, 3};
//    assert(digits_forward_order::sum_lists({9, 7, 8}, {6, 8, 5}) == ref);

    return 0;
}
