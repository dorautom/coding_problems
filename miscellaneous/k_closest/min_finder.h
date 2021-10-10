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

#include <functional>
#include <vector>
#include <tuple>
#include <cassert>


template <typename Distance, class Item>
class MinFinder
{
public:
    using DistanceItem = std::tuple<Distance, Item>;

    struct DistanceCompareLess
    {
        bool operator()(DistanceItem& a, DistanceItem& b)
        {
            return std::get<0>(a) <= std::get<0>(b);
        }
    };
    using MaxHeap = std::priority_queue<DistanceItem, std::vector<DistanceItem>, DistanceCompareLess>;

    MinFinder(std::function<Distance(const Item&)> metric, int k) : k_(k), metric_(metric) 
    {
        assert(k > 0);
    }
    
    void push(const std::vector<Item>& items)
    {
        for (auto& item : items)
        {
            Distance distance = metric_(item);
            if (k_closest_.size() < k_)
            {
                k_closest_.push(std::make_tuple(distance, item));
            }
            else
            if (distance < std::get<0>(k_closest_.top()))
            {
                k_closest_.pop();
                k_closest_.push(std::make_tuple(distance, item));
            }
        }
    }

    std::vector<DistanceItem> get_minimal() const
    {
        std::vector<DistanceItem> result;
        result.reserve(k_);
        MaxHeap max_heap = k_closest_;
        while (!max_heap.empty())
        {
            result.push_back(max_heap.top());
            max_heap.pop();
        }
        return result;
    }

protected:
    int k_;
    std::function<Distance(Item)> metric_;
    MaxHeap k_closest_;
};
