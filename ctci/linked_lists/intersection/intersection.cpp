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

// problem: given two singly linked lists, determine if the two lists intersect. Return the intersecting node. Note that intersection
//          is defined based on reference, not value.

#include <forward_list>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <functional>
#include <optional>

typedef int item_type;

// type that behaves like reference but can be stored as static data member
template <typename T>
class const_reference_type
{
    typedef const T& const_reference;
    const T* cptr;
 public:
    const_reference_type(const_reference cref) : cptr(&cref) {}

    operator const_reference () const
    {
        return *cptr;
    }

    T value() const
    {
        return *cptr;
    }

    bool operator ==(const const_reference_type& other)
    {
        return cptr == other.cptr;
    }
};

typedef const_reference_type<item_type> item_reference_type;

// TODO: change std forward list to self-implemented list in order to access nodes by reference

// returns reference to 1st intersecting item of `list1` and `list2` or empty if `list1` and `list2` do not intersect
std::optional<item_reference_type> intersect(const std::forward_list<item_type>& list1, const std::forward_list<item_type>& list2)
{
    auto it1 = list1.cbegin();
    auto it2 = list2.cbegin();
    int len1 = 0;
    int len2 = 0;
    // if one of lists is empty we are done
    if (it1 == list1.cend() || it2 == list2.cend())
        return std::optional<item_reference_type>();
    item_reference_type ref_tail1 = *it1;
    item_reference_type ref_tail2 = *it2;
    while (it1 != list1.cend())
    {
        ref_tail1 = *it1;
        it1++;
        len1++;
    }
    while (it2 != list2.cend())
    {
        ref_tail2 = *it2;
        it2++;
        len2++;
    }
    if (ref_tail1 != ref_tail2)
        return std::optional<item_reference_type>();
    // now we know there is intersection    
    it1 = list1.cbegin();
    it2 = list2.cbegin();
    int diff = len1 - len2;
    if (diff < 0)
    {
        std::swap(it1, it2);
        diff *= -1;
    }
    // it2 points to shorter or equal length list
    while (diff)
    {
        it1++;
        diff--;
    }
    // now there is the same number of nodes from it1 and it2 to the end
    typedef std::forward_list<item_type>::const_iterator iterator_type;
    auto equal_by_reference = [](iterator_type iter1, iterator_type iter2) -> bool
    {
        item_reference_type item1 = *iter1;
        item_reference_type item2 = *iter2;
        return item1 == item2;
    };
    while (!equal_by_reference(it1++, it2++));
    return *it1;
}

bool verify(const std::forward_list<item_type>& in1, const std::forward_list<item_type>& in2, std::optional<item_reference_type> out_ref, 
            std::function<std::optional<item_reference_type>(const std::forward_list<item_type>&, const std::forward_list<item_type>&)> tested_fun)
{
    auto result = tested_fun(in1, in2);
    if (result.has_value())
    {
        std::cout << "intersection found: " << result->value() << '\n';
    }

    return (*result == *out_ref || 
           (!result.has_value() && !out_ref.has_value()));
}

int main()
{
    std::forward_list<item_type> list1;
    std::forward_list<item_type> list2;
    std::optional<item_reference_type> no_intersection;
    assert(verify(list1, list2, no_intersection, intersect));
    return 0;
}
