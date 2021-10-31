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

#include <string>
#include <cassert>
#include "lru_cache.h"

void verify()
{
    lru_cache::Cache<int, std::string> cache(3);
    cache.set(1, "1");
    // lru = 1
    cache.set(2, "2");
    // lru = 2 1
    cache.set(10, "10");
    // lru = 10 2 1

    auto item = cache.get(1);   
    // lru = 1 10 2
    assert(item.has_value());
    assert(*item == "1");

    item = cache.get(2);   
    // lru = 2 1 10
    assert(item.has_value());
    assert(*item == "2");

    item = cache.get(4);
    assert(!item.has_value());

    item = cache.get(10);
    // lru = 10 2 1
    assert(item.has_value());
    assert(*item == "10");

    // 1 is evicted
    cache.set(4, "4");
    // lru = 4 10 2

    item = cache.get(1);   
    assert(!item.has_value());

    item = cache.get(4);   
    // lru = 4 10 2
    assert(item.has_value());
    assert(*item == "4");

    // 2 is updated
    cache.set(2, "22");
    // lru = 22 4 10

    // 10 is evicted
    cache.set(3, "3");
    // lru = 3 22 4

    item = cache.get(10);   
    assert(!item.has_value());

    item = cache.get(2);   
    // lru = 22 3 4
    assert(item.has_value());
    assert(*item == "22");

    item = cache.get(3);   
    // lru = 22 3 4
    assert(item.has_value());
    assert(*item == "3");

    item = cache.get(4);   
    // lru = 22 3 4
    assert(item.has_value());
    assert(*item == "4");
}

int main()
{
    verify();
    return 0;
}
