#include "../include/monotoneFunctions.hpp"
#include "../include/triangulationFunctions.hpp"
#include "../include/point.hpp"
#include <queue>
#include <vector>
#include <set>
#include <cmath>

#include <stdio.h>

void findCorrectEdgeChain(Point *p1, Point *p2, HalfEdge **from, HalfEdge **to)
{
  fprintf(stderr, "\nfindCorrectEdgeChain\n");
      HalfEdge *tmp,
      *t, *f;
  for (const auto &face : Face::faceList)
  {
    
    tmp = face->edgeChain();
    f = nullptr;
    t = nullptr;
    do
    {
      if (tmp->from() == p1)
      {
        if (f == nullptr)
        {
          f = tmp;
        }
        else
        {
          t = tmp;
        }
      }
      if (tmp->from() == p2)
      {
        if (f == nullptr)
        {
          f = tmp;
        }
        else
        {
          t = tmp;
        }
      }
      tmp = tmp->next();
    } while (tmp != face->edgeChain());
    if (f != nullptr && t != nullptr)
    {
      *from = f;
      *to = t;
      break;
    }
  }
  fprintf(stderr, "EXIT findCorrectEdgeChain\n");
}

bool edgePointerComparisonFunc(const HalfEdge *a, const HalfEdge *b)
{
  return a->from()->x < b->from()->x;
}

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

vertexType computeVertexType(HalfEdge *e)
{
  auto vertex = e->from();
  auto prevVertex = e->prev()->from();
  auto nextVertex = e->to();

  // One neighbor is above and one neighbor is bellow. Therefore the vertex is regular
  if (((*vertex) > (*prevVertex) && (*vertex) < (*nextVertex)) || ((*vertex) < (*prevVertex) && (*vertex) > (*nextVertex)))
  {
    return regular;
  }
  else if ((*vertex) > (*prevVertex) && (*vertex) > (*nextVertex))
  {
    float dot = (prevVertex->x - vertex->x) * (nextVertex->x - vertex->x) + (prevVertex->y - vertex->y) * (nextVertex->y - vertex->y);
    float det = (prevVertex->x - vertex->x) * (nextVertex->y - vertex->y) - (prevVertex->y - vertex->y) * (nextVertex->x - vertex->x);

    auto angle = atan2(det, dot);
    if (angle < 0)
      return split;
    else
      return start;
  }
  else if ((*vertex) < (*prevVertex) && (*vertex) < (*nextVertex))
  {
    float dot = (prevVertex->x - vertex->x) * (nextVertex->x - vertex->x) + (prevVertex->y - vertex->y) * (nextVertex->y - vertex->y);
    float det = (prevVertex->x - vertex->x) * (nextVertex->y - vertex->y) - (prevVertex->y - vertex->y) * (nextVertex->x - vertex->x);

    auto angle = atan2(det, dot);
    if (angle < 0)
      return merge;
    else
      return end;
  }
  return regular;
}

typedef std::set<HalfEdge *, bool (*)(const HalfEdge *, const HalfEdge *)> edgeSet;

HalfEdge *getPredecessor(edgeSet t, HalfEdge *e)
{
  auto tmp = t.lower_bound(e);
  auto begin = t.begin();
  auto end = t.end();
  auto size = t.size();
  auto it = tmp == t.end() ? std::prev(t.end()) : --tmp;
  return *it;
}

void makeMonotone(HalfEdge *dcel)
{
  std::priority_queue<HalfEdge *, std::vector<HalfEdge *>, edgePointerComparison> q;
  std::set<HalfEdge *, bool (*)(const HalfEdge *, const HalfEdge *)> t(&edgePointerComparisonFunc);
  auto tmpEdge = dcel;

  HalfEdge *fromEdge, *toEdge;

  // Construct priority queue
  do
  {
    q.push(tmpEdge);
    tmpEdge->from()->type = computeVertexType(tmpEdge);
    tmpEdge->setHelper(tmpEdge);
    tmpEdge = tmpEdge->next();
  } while (tmpEdge != dcel);

  while (!q.empty())
  {
    auto edgeVertex = q.top();
    q.pop();
    switch (edgeVertex->from()->type)
    {
    case start:
      t.insert(edgeVertex);
      edgeVertex->setHelper(edgeVertex);
      break;
    case end:
      if (edgeVertex->prev()->helper()->from()->type == merge)
      {
        findCorrectEdgeChain(edgeVertex->from(), edgeVertex->prev()->helper()->from(), &fromEdge, &toEdge);
        insertDiagonal(fromEdge, toEdge);
      }
      t.erase(edgeVertex->prev());
      break;
    case split:
      tmpEdge = getPredecessor(t, edgeVertex);
      findCorrectEdgeChain(edgeVertex->from(), tmpEdge->helper()->from(), &fromEdge, &toEdge);
      insertDiagonal(fromEdge, toEdge);
      tmpEdge->setHelper(edgeVertex);
      edgeVertex->setHelper(edgeVertex);
      t.insert(edgeVertex);
      break;
    case merge:
      if (edgeVertex->next()->helper()->from()->type == merge)
      {
        findCorrectEdgeChain(edgeVertex->from(), edgeVertex->next()->helper()->from(), &fromEdge, &toEdge);
        insertDiagonal(fromEdge,toEdge);
      }
      t.erase(edgeVertex->next());
      tmpEdge = getPredecessor(t, edgeVertex);
      if (tmpEdge->helper()->from()->type == merge)
      {
        findCorrectEdgeChain(edgeVertex->from(), tmpEdge->helper()->from(), &fromEdge, &toEdge);
        insertDiagonal(fromEdge, toEdge);
      }
      tmpEdge->setHelper(edgeVertex);
      break;
    case regular:
      if (*(edgeVertex->next()) > *edgeVertex)
      {
        if (edgeVertex->next()->helper()->from()->type == merge)
        {
          findCorrectEdgeChain(edgeVertex->from(), edgeVertex->next()->helper()->from(), &fromEdge, &toEdge);
          insertDiagonal(fromEdge, toEdge);
        }
        t.erase(edgeVertex->next());
        edgeVertex->setHelper(edgeVertex);
        t.insert(edgeVertex);
      }
      else
      {
        tmpEdge = getPredecessor(t, edgeVertex);
        if (tmpEdge->helper()->from()->type == merge)
        {
          findCorrectEdgeChain(edgeVertex->from(), tmpEdge->helper()->from(), &fromEdge, &toEdge);
          insertDiagonal(fromEdge, toEdge);
        }
        tmpEdge->setHelper(edgeVertex);
      }
      break;
    }
  }
}
