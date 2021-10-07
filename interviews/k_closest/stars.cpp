// priority_queue<T, Compare=less>
//   - top()
//   - push()
//   - pop()

#include <cmath>
#include <vector>
#include <queue>
#include <tuple>
#include <iostream>
#include <cassert>

typedef uint32_t star_id;

struct star
{
  star_id id;
  float x;
  float y;
  float z;
  star(star_id id0, float x0, float y0, float z0) : id(id0), x(x0), y(y0), z(z0)
  {
  }
};

double distance(const star& a, const star& b)
{
  return std::sqrt(std::pow(static_cast<double>(a.x - b.x), 2) + std::pow(static_cast<double>(a.y - b.y), 2) + std::pow(static_cast<double>(a.z - b.z), 2));
}

double distance_from_earth(const star& a)
{
  return std::sqrt(std::pow(static_cast<double>(a.x), 2) + std::pow(static_cast<double>(a.y), 2) + std::pow(static_cast<double>(a.z), 2));
}

std::vector<star> getInputData()
{
    return std::vector<star>(
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

// TBD: detach algorihtm from specific data structure using template and custom compare function
std::vector<star_id> getClosest(const std::vector<star>& stars, uint32_t k)
{
  typedef std::tuple<double, star_id> star_distance;
  std::priority_queue<star_distance, std::vector<star_distance>> k_closest;
  for (auto& star : stars)
  {
    double distance = distance_from_earth(star);
    if (k_closest.size() < k)
    {
      k_closest.push(std::make_tuple(distance, star.id));
    }
    else
    {
      if (distance < std::get<0>(k_closest.top()))
      {
        k_closest.pop();
        k_closest.push(std::make_tuple(distance, star.id));
      }
      else // what about equal?
      {

      }
    }
  }

  std::vector<star_id> result;
  result.reserve(k);
  while (!k_closest.empty())
  {
    result.push_back(std::get<1>(k_closest.top()));
    k_closest.pop();
  }
  return result;
}

int main()
{
  uint32_t k = 5;
  std::vector<star_id> k_closest = getClosest(getInputData(), k);
  std::cout << k << "-closest:\n";
  assert(k_closest.size() == k);
  for (auto id : k_closest)
  {
    std::cout << id << '\n';
  }
  return 0;
}
