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

#include <vector>
#include <string>
#include <cassert>

namespace string_builder
{

// class string builder allows to concatenate many strings of length ~n in O(n) time
// otherwise concatenating many strings iteratively takes O(n^2) time
class string_builder
{
    std::vector<std::string> items_;
    size_t total_length_;
public:
    string_builder() : total_length_(0)
    {
    }

    string_builder(size_t items_count) : total_length_(0)
    {
        items_.reserve(items_count);
    }

    void add(const std::string& str)
    {
        items_.push_back(str);
        total_length_ += str.size();
    }

    string_builder& operator += (const std::string& str)
    {
        add(str);
        return *this;
    }

    std::string concatenate() const
    {
        std::string result;
        result.resize(total_length_);
        size_t pos = 0;
        for (auto item : items_)
        {
            result.replace(pos, item.size(), item);
            pos += item.size();
        }
        assert(pos == total_length_);
        assert(result.size() == total_length_);
        return result;
    }

    std::string operator ()() const
    {
        return concatenate();
    }

    size_t size() const
    {
        return total_length_;
    }

};

}
