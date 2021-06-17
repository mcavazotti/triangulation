#ifndef HALF_EDGE_H
#define HALF_EDGE_H

#include "point.hpp"

template <typename T>
class HalfEdge
{
public:
  HalfEdge() : p1(nullptr), p2(nullptr), p(nullptr), n(nullptr), t(nullptr), h(nullptr)
  {
#ifdef DEBUG
    edgeList.push_back(this);
#endif
  }
  HalfEdge(Point<T> *a1) : p1(a1), p2(nullptr), p(nullptr), n(nullptr), t(nullptr), h(nullptr)
  {
#ifdef DEBUG
    edgeList.push_back(this);
#endif
  }
  HalfEdge(Point<T> *a1, Point<T> *a2) : p1(a1), p2(a2), p(nullptr), n(nullptr), t(nullptr), h(nullptr)
  {
#ifdef DEBUG
    edgeList.push_back(this);
#endif
  }
  HalfEdge(Point<T> *a1, Point<T> *a2, HalfEdge<T> *prev, HalfEdge<T> *next, HalfEdge<T> *twin) : p1(a1), p2(a2), p(prev), n(next), t(twin), h(nullptr)
  {
#ifdef DEBUG
    edgeList.push_back(this);
#endif
  }

  bool operator>(const HalfEdge<T> &e) const
  {
    return (*p1) > (*(e.from()));
  }

  bool operator<(const HalfEdge<T> &e) const
  {
    return (*p1) < (*(e.from()));
  }

  bool operator>=(const HalfEdge<T> &e) const
  {
    return (*p1) >= (*(e.from()));
  }

  bool operator<=(const HalfEdge<T> &e) const
  {
    return (*p1) <= (*(e.from()));
  }

  Point<T> *from() const { return p1; }
  Point<T> *to() const { return p2; }
  HalfEdge<T> *prev() const { return p; }
  HalfEdge<T> *next() const { return n; }
  HalfEdge<T> *twin() const { return t; }
  HalfEdge<T> *helper() const { return h; }

  void setFrom(Point<T> *a) { p1 = a; }
  void setTo(Point<T> *a) { p2 = a; }
  void setPoints(Point<T> *a1, Point<T> *a) { p2 = a; }
  void setPrev(HalfEdge *e) { p = e; }
  void setNext(HalfEdge *e) { n = e; }
  void setTwin(HalfEdge *e) { t = e; }
  void setHelper(HalfEdge *e) { h = e; }

#ifdef DEBUG
  static std::vector<HalfEdge<T> *> edgeList;
#endif

private:
  Point<T> *p1, *p2;
  HalfEdge<T> *p, *n, *t, *h;

#ifdef DEBUG
  static int counter;
#endif
};

#ifdef DEBUG
template <typename T>
int HalfEdge<T>::counter = 0;
template <typename T>
std::vector<HalfEdge<T> *> HalfEdge<T>::edgeList = std::vector<HalfEdge<T> *>();
#endif

#endif