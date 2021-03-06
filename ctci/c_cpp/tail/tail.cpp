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
#include <fstream>
#include <string>
#include <list>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "need file name argument\n";
        return 0;
    }
    const char* const filename = argv[1];
    int lines_to_print = 5;
    std::cout << "Input file name: " << filename << '\n';
    if (argc > 2)
    {
        lines_to_print = std::atoi(argv[2]);
    }
    std::cout << "Lines to print: " << lines_to_print << '\n';

    std::ifstream input(filename, std::ios_base::in);
    if (!input.good())
    {
        std::cerr << "error opening file!\n";
        return -1;
    }

    input.seekg(0, std::ios_base::end);
    std::cout << "file size: " << input.tellg() << '\n';
    input.seekg(0, std::ios_base::beg);

    std::string line;
    std::list<std::string> tail;

    while (!input.eof())
    {
        std::getline(input, line);
        tail.push_back(line);
        if (tail.size() > lines_to_print)
        {
            tail.pop_front();
        }
    }

    std::cout << "Last " << lines_to_print << " lines\n";

    for (auto s : tail)
    {
        std::cout << s << '\n';
    }

    return 0;
}
