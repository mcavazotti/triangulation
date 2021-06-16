#ifndef POINT_H
#define POINT_H

#include <vector>

typedef enum
{
  start,
  end,
  regular,
  split,
  merge,
} vertexType;

template <typename T>
class Point
{
public:
  Point() : x(0), y(0), id(++counter)
  {
    pointList.push_back(this);
  }
  Point(T a1, T a2) : x(a1), y(a2), id(++counter)
  {
    pointList.push_back(this);
  }

  bool operator==(const Point &p) const
  {
    return x == p.x && y == p.y;
  }

  bool operator!=(const Point &p) const
  {
    return x != p.x && y != p.y;
  }

  bool operator>(const Point &p) const
  {
    if (y != p.y)
      return y > p.y;
    else
      return x < p.x;
  }

  bool operator<(const Point &p) const
  {
    if (y != p.y)
      return y < p.y;
    else
      return x > p.x;
  }

  bool operator>=(const Point &p) const
  {
    return this == p || this > p;
  }

  bool operator<=(const Point &p) const
  {
    return this == p || this < p;
  }

public:
  T x, y;
  vertexType type;
  const int id;
  static std::vector<Point<T> *> pointList;

private:
  static int counter;
};

typedef Point<int> PointInt;

template <typename T>
int Point<T>::counter = 0;
template <typename T>
std::vector<Point<T> *> Point<T>::pointList = std::vector<Point<T> *>();

#endif // POINT_H