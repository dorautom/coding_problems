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
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <cassert>

typedef uint32_t PointID;

struct Point
{
  PointID id;
  float x;
  float y;
  float z;

  // Point(PointID id0, float x0, float y0, float z0) : id(id0), x(x0), y(y0), z(z0)
  // {
  // }
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
                {0, .1f, .5f, .2f},
                {1, 30, 40, 50},
                {2, 1, 1, 1},
                {3, 3.0f, 4.5f, 5.0f},
                {4, 2.0f, 1.0f, 1.0f},
                {5, 18.2f, 4.1f, 10.0f},
                {6, 5.0f, 6.0f, 3.0f},
                {7, .01f, .02f, .04f},
                {8, 5.0f, 6.0f, 3.0f},
        }
    );
}

typedef std::tuple<double, Point> PointDistance;

struct PointDistanceCompareLess
{
  bool operator()(PointDistance& a, PointDistance& b)
  {
    return std::get<0>(a) <= std::get<0>(b);
  }
};

// TBD: detach algorihtm from specific data structure using template and custom compare function
std::vector<PointDistance> getClosest(const std::vector<Point>& points, uint32_t k)
{
  std::priority_queue<PointDistance, std::vector<PointDistance>, PointDistanceCompareLess> k_closest;
  for (const auto& point : points)
  {
    double distance = distance_from_center(point);
    if (k_closest.size() < k)
    {
      PointDistance item = std::make_tuple(distance, point);
      k_closest.push(item);
    }
    else
    {
      if (distance < std::get<0>(k_closest.top()))
      {
        k_closest.pop();
        k_closest.push(std::make_tuple(distance, point));
      }
    }
  }

  std::vector<PointDistance> result;
  result.reserve(k);
  while (!k_closest.empty())
  {
    result.push_back(k_closest.top());
    k_closest.pop();
  }
  return result;
}

int main()
{
  uint32_t k = 3;
  std::vector<PointDistance> k_closest = getClosest(getInputData(), k);
  std::cout << k << "-closest:\n";
  assert(k_closest.size() == k);
  for (auto item : k_closest)
  {
    std::cout << std::get<0>(item) << '\n';
  }
  return 0;
}
