#ifndef SORTING_FUNC_H
#define SORTING_FUNC_H

#include "halfEdge.hpp"

bool edgePointerHorizontalComparisonFunc(const HalfEdge *a, const HalfEdge *b);
bool edgePointerVerticalComparisonFunc(const HalfEdge *a, const HalfEdge *b);
double computeAngle(Point *p1, Point *p2, Point *p3);

class edgePointerComparison
{
  bool reverse;

public:
  edgePointerComparison(const bool &revparam = false)
  {
    reverse = revparam;
  }
  bool operator()(HalfEdge *a, HalfEdge *b) const
  {
    if (reverse)
      return (*a) > (*b);
    else
      return (*a) < (*b);
  }
};
#endif