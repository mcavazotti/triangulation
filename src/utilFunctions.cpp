#include "../include/utilFunctions.hpp"
#include "../include/point.hpp"

#include <cmath>

bool edgePointerHorizontalComparisonFunc(const HalfEdge *a, const HalfEdge *b)
{
  return a->from()->x < b->from()->x;
}

bool edgePointerVerticalComparisonFunc(const HalfEdge *a, const HalfEdge *b)
{
  return (*a->from()) > (*b->from());
}

double computeAngle(Point *p1, Point *p2, Point *p3)
{
  float dot = (p1->x - p2->x) * (p3->x - p2->x) + (p1->y - p2->y) * (p3->y - p2->y);
  float det = (p1->x - p2->x) * (p3->y - p2->y) - (p1->y - p2->y) * (p3->x - p2->x);

  return atan2(det, dot);
}