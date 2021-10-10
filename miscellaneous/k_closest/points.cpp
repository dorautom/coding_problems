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

#include <cmath>
#include <iostream>
#include <cassert>
#include "min_finder.h"

// Problem: from N points (x,y,z) find k closest to the centre (0,0,0)

typedef uint32_t PointID;

struct Point
{
  PointID id;
  float x;
  float y;
  float z;
};

double distance(const Point& a, const Point& b)
{
  return std::sqrt(std::pow(static_cast<double>(a.x - b.x), 2) + std::pow(static_cast<double>(a.y - b.y), 2) + std::pow(static_cast<double>(a.z - b.z), 2));
}

double distance_from_center(const Point& a)
{
  return std::sqrt(std::pow(static_cast<double>(a.x), 2) + std::pow(static_cast<double>(a.y), 2) + std::pow(static_cast<double>(a.z), 2));
}

std::vector<Point> getInputData()
{
    return std::vector<Point>(
            {
                {1, 30, 40, 50},
                {2, 1, 1, 1},
                {3, 3.0f, 4.5f, 5.0f},
                {4, 2.0f, 1.0f, 1.0f},
                {5, 18.2f, 4.1f, 10.0f},
                {6, 5.0f, 6.0f, 3.0f},
                {7, .01f, .02f, .04f},
                {8, 5.0f, 6.0f, 3.0f},
                {9, .1f, .5f, .2f},
        }
    );
}


int main()
{
  const uint32_t k = 5;
  const Point center = {0, 0., 0., 0.}; 
  auto distance_from_center = [&](const Point& p){ return distance(center, p);};

  MinFinder<double, Point> finder(distance_from_center, k);
  finder.push(getInputData());
  auto k_closest = finder.get_minimal();

  std::cout << k << "-closest:\n";
  assert(k_closest.size() == k);
  for (auto item : k_closest)
  {
    std::cout << std::get<0>(item) << '\n';
  }
  return 0;
}
