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

// https://projecteuler.net/problem=15

#include <iostream>
#include <vector>

template <typename T>
void print(std::vector<T> vec)
{
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec.at(i) << ' ';
    std::cout << '\n';
}

long int lattice(int m)
{
    if (m == 1)
    {
        return 2;
    }
    std::vector<long int> accu(m + 1, 1);
    for (int j = 0; j < m; j++)
    {
        print(accu);
        for (int i = 0; i < m; i++)
        {
            accu.at(i + 1) += accu.at(i);
        }
    }
    print(accu);
    return accu.at(m);
}

int main()
{
    std::cout << lattice(20) << '\n';
    return 0;
}
