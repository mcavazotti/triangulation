#include "../include/monotoneFunctions.hpp"
#include "../include/point.hpp"
#include <queue>
#include <vector>
#include <set>
#include <cmath>

#include <stdio.h>
bool edgePointerComparisonFunc(const HalfEdge<int> *a, const HalfEdge<int> *b)
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
  bool operator()(HalfEdge<int> *a, HalfEdge<int> *b) const
  {
    if (reverse)
      return (*a) > (*b);
    else
      return (*a) < (*b);
  }
};

vertexType computeVertexType(HalfEdge<int> *e)
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

void insertDiagonal(HalfEdge<int> *fromEdge, HalfEdge<int> *toEdge)
{
  auto diagonal = new HalfEdge<int>(fromEdge->from(), toEdge->from(), fromEdge->twin(), toEdge->prev()->twin(), nullptr);
  fromEdge->twin()->setNext(diagonal);
  toEdge->prev()->twin()->setPrev(diagonal);

  auto diagonalTwin = new HalfEdge<int>(toEdge->from(), fromEdge->from(), toEdge->twin(), fromEdge->prev()->twin(), diagonal);
  diagonal->setTwin(diagonalTwin);
  toEdge->twin()->setNext(diagonalTwin);
  fromEdge->prev()->twin()->setPrev(diagonalTwin);
}

typedef std::set<HalfEdge<int> *, bool (*)(const HalfEdge<int> *, const HalfEdge<int> *)> edgeSet;

HalfEdge<int> *getPredecessor(edgeSet t, HalfEdge<int> *e)
{
  auto tmp = t.lower_bound(e);
  auto begin = t.begin();
  auto end = t.end();
  auto size = t.size();
  auto it = tmp == t.end() ? std::prev(t.end()) : --tmp;
  return *it;
}

void makeMonotone(HalfEdge<int> *dcel)
{
  std::priority_queue<HalfEdge<int> *, std::vector<HalfEdge<int> *>, edgePointerComparison> q;
  std::set<HalfEdge<int> *, bool (*)(const HalfEdge<int> *, const HalfEdge<int> *)> t(&edgePointerComparisonFunc);
  auto tmpEdge = dcel;

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
        insertDiagonal(edgeVertex, edgeVertex->prev()->helper());
      }
      t.erase(edgeVertex->prev());
      break;
    case split:
      tmpEdge = getPredecessor(t, edgeVertex);
      insertDiagonal(edgeVertex, tmpEdge->helper());
      tmpEdge->setHelper(edgeVertex);
      edgeVertex->setHelper(edgeVertex);
      t.insert(edgeVertex);
      break;
    case merge:
      if (edgeVertex->prev()->helper()->from()->type == merge)
      {
        insertDiagonal(edgeVertex, edgeVertex->prev()->helper());
      }
      t.erase(edgeVertex->prev());
      tmpEdge = getPredecessor(t, edgeVertex);
      if (tmpEdge->helper()->from()->type == merge)
      {
        insertDiagonal(edgeVertex, tmpEdge->helper());
      }
      tmpEdge->setHelper(edgeVertex);
      break;
    case regular:
      if (*(edgeVertex->next()) > *edgeVertex)
      {
        if (edgeVertex->prev()->helper()->from()->type == merge)
        {
          insertDiagonal(edgeVertex, edgeVertex->prev()->helper());
        }
        t.erase(edgeVertex->prev());
        edgeVertex->setHelper(edgeVertex);
        t.insert(edgeVertex);
      }
      else
      {
        tmpEdge = getPredecessor(t, edgeVertex);
        if (tmpEdge->helper()->from()->type == merge)
        {
          insertDiagonal(edgeVertex, tmpEdge->helper());
        }
        tmpEdge->setHelper(edgeVertex);
      }
      break;
    }
  }
}
