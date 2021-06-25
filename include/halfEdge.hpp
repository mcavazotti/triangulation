#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "point.hpp"

class Face;

/**
 * This class represents a node for the DCEL
*/
class HalfEdge
{
public:
  HalfEdge() : p1(nullptr), p2(nullptr), p(nullptr), n(nullptr), t(nullptr), h(nullptr), f(nullptr), chain(0) {}
  HalfEdge(Point *a1) : p1(a1), p2(nullptr), p(nullptr), n(nullptr), t(nullptr), h(nullptr), f(nullptr), chain(0) {}
  HalfEdge(Point *a1, Point *a2) : p1(a1), p2(a2), p(nullptr), n(nullptr), t(nullptr), h(nullptr), f(nullptr), chain(0) {}
  HalfEdge(Point *a1, Point *a2, HalfEdge *prev, HalfEdge *next, HalfEdge *twin) : p1(a1), p2(a2), p(prev), n(next), t(twin), h(nullptr), f(nullptr), chain(0) {}

  bool operator>(const HalfEdge &e) const
  {
    return (*p1) > (*(e.from()));
  }

  bool operator<(const HalfEdge &e) const
  {
    return (*p1) < (*(e.from()));
  }

  bool operator>=(const HalfEdge &e) const
  {
    return (*p1) >= (*(e.from()));
  }

  bool operator<=(const HalfEdge &e) const
  {
    return (*p1) <= (*(e.from()));
  }

  Point *from() const { return p1; }
  Point *to() const { return p2; }
  HalfEdge *prev() const { return p; }
  HalfEdge *next() const { return n; }
  HalfEdge *twin() const { return t; }
  HalfEdge *helper() const { return h; }
  Face *face() const { return f; }

  void setFrom(Point *a) { p1 = a; }
  void setTo(Point *a) { p2 = a; }
  void setPoints(Point *a1, Point *a) { p2 = a; }
  void setPrev(HalfEdge *e) { p = e; }
  void setNext(HalfEdge *e) { n = e; }
  void setTwin(HalfEdge *e) { t = e; }
  void setHelper(HalfEdge *e) { h = e; }
  void setFace(Face *fa) { f = fa; }

public:
  int chain;

private:
  Point *p1, *p2;
  HalfEdge *p, *n, *t, *h;
  Face *f;
};

#endif