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

class Point
{
public:
  Point() : x(0), y(0), id(++counter)
  {
    pointList.push_back(this);
  }
  Point(int a1, int a2) : x(a1), y(a2), id(++counter)
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
    return *this == p || *this > p;
  }

  bool operator<=(const Point &p) const
  {
    return *this == p || *this < p;
  }

public:
  int x, y;
  vertexType type;
  const int id;
  static std::vector<Point *> pointList;

private:
  static int counter;
};




inline int Point::counter = 0;

inline std::vector<Point *> Point::pointList = std::vector<Point *>();

#endif // POINT_H