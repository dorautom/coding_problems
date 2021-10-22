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

/* problem: compress string if it is shorter after compression
   example: "aabcccccaaa" -> "2a1b5c3a", "abc" -> "abc"
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>
#include <limits>
#include <cmath>

std::string compress(const std::string& input)
{
    std::string output;
    long int max_n = std::numeric_limits<long int>::max();
    int n = 1;
    char c = 0;
    auto chunk = [&]() { std::stringstream s; s << n; s << c; return s.str(); };
    const char* next = input.c_str();
    c = *(next++);
    output.reserve(input.size());
    while (c)
    {
        if (c == *next)
        {
            if (n == max_n)
            {
                std::cout << "optimization works, input: " << input << ", output: " << output << ", max_n == " << max_n << '\n';
                return input;
            } 
            n++;
        }
        else
        {
            auto s = chunk();
            if (output.size() + s.size() > input.size()) 
                return input;
            output += s;
            n = 1;
            // recalculate n_max
            int chars_left = input.size() - output.size() - 1;
            max_n = chars_left >= 0 ? std::pow(10, chars_left) - 1 : 0;
        }
        c = *(next++);
    }
    return output;
}

int main(int argc, char** argv)
{
    auto test = [] (const std::string& in, const std::string& out) -> bool { return out == compress(in); };
    assert(test("aabcccccaaa","2a1b5c3a"));
    assert(test("abc", "abc"));
    assert(test("", ""));
    assert(test("aa", "2a"));
    assert(test("aabb", "2a2b"));
    assert(test("aabb", "2a2b"));
    const char* x = "yxyxyxyxyxyxyxybbbbbbbbbbbbbbbbb";
    assert(test(x, x)); // test optimization
    return 0;
}
