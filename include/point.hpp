#ifndef POINT_H
#define POINT_H

template <typename T>
class Point
{
public:
  Point() : x(0), y(0) {}
  Point(T a1, T a2) : x(a1), y(a2) {}

  bool operator==(Point p)
  {
    return x == p.x && y == p.y;
  }

  bool operator!=(Point p)
  {
    return x != p.x && y != p.y;
  }

  bool operator>(Point p)
  {
    if (y != p.y)
      return y > p.y;
    else
      return x > p.x;
  }

  bool operator<(Point p)
  {
    if (y != p.y)
      return y < p.y;
    else
      return x < p.x;
  }

  bool operator>=(Point p)
  {
    return this == p || this > p;
  }

  bool operator<=(Point p)
  {
    return this == p || this < p;
  }

public:
  T x, y;
};

typedef Point<int> PointInt;

#endif // POINT_H