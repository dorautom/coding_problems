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

// problem: implement LRU cache (Least Recently Used item is evicted first) of given max capacity
// the cache must be fast, so access (read / write) must be in O(1) time complexity

#include <unordered_map>
#include <list>
#include <optional>

namespace lru_cache
{

template <typename key_t, typename value_t>
class Cache
{
        using key_value = std::pair<key_t, value_t>;
        using iterator = typename std::list<key_value>::iterator;
        std::unordered_map<key_t, iterator> map_;
        std::list<key_value> values_;
        size_t capacity_;

    public:
        Cache(size_t capacity) : capacity_(capacity) {}

        std::optional<value_t> get(const key_t& key)
        {
            if (map_.count(key) == 0)
            {
                return std::optional<value_t>();
            }
            auto iter = map_[key];
            auto elem = *iter;
            values_.erase(iter);
            values_.push_front(elem);
            map_.emplace(std::make_pair(key, values_.begin()));
            return std::get<1>(elem);
        }

        void set(const key_t& key, const value_t& value)
        {
            if (map_.count(key))
            {
                auto iter = map_[key];
                values_.erase(iter);
            }
            values_.push_front(std::make_pair(key, value));
            map_.emplace(std::make_pair(key, values_.begin()));
            if (values_.size() > capacity_)
            {
                auto lru_item = values_.back();
                map_.erase(std::get<0>(lru_item));
                values_.pop_back();                
            }
        }
};

}

