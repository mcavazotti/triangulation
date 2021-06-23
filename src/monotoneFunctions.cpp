#include "../include/monotoneFunctions.hpp"
#include "../include/triangulationFunctions.hpp"
#include "../include/point.hpp"
#include <queue>
#include <vector>
#include <set>
#include <cmath>

#include <stdio.h>
bool edgePointerComparisonFunc(const HalfEdge *a, const HalfEdge *b)
{
  return a->from()->x > b->from()->x;
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
    if (angle > 0)
      return split;
    else
      return start;
  }
  else if ((*vertex) < (*prevVertex) && (*vertex) < (*nextVertex))
  {
    float dot = (prevVertex->x - vertex->x) * (nextVertex->x - vertex->x) + (prevVertex->y - vertex->y) * (nextVertex->y - vertex->y);
    float det = (prevVertex->x - vertex->x) * (nextVertex->y - vertex->y) - (prevVertex->y - vertex->y) * (nextVertex->x - vertex->x);

    auto angle = atan2(det, dot);
    if (angle > 0)
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
  if(tmp == t.end()){
    // fprintf(stderr, "\n\nSET END\n\n");
  }
  auto it = tmp == t.end() ? std::prev(t.end()) : --tmp;
  return *it;
}

void makeMonotone(HalfEdge *dcel)
{
  std::priority_queue<HalfEdge *, std::vector<HalfEdge *>, edgePointerComparison> q;
  std::set<HalfEdge *, bool (*)(const HalfEdge *, const HalfEdge *)> t(&edgePointerComparisonFunc);
  auto tmpEdge = dcel->twin();

  // Construct priority queue
  do
  {
    q.push(tmpEdge);
    tmpEdge->from()->type = computeVertexType(tmpEdge);
    tmpEdge->setHelper(tmpEdge);
    tmpEdge = tmpEdge->next();
  } while (tmpEdge != dcel->twin());

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
      if (edgeVertex->next()->helper()->from()->type == merge)
      {
        insertDiagonal(edgeVertex, edgeVertex->next()->helper());
      }
      t.erase(edgeVertex->next());
      break;
    case split:
      tmpEdge = getPredecessor(t, edgeVertex);
      insertDiagonal(edgeVertex, tmpEdge->helper());
      tmpEdge->setHelper(edgeVertex);
      edgeVertex->setHelper(edgeVertex);
      t.insert(edgeVertex);
      break;
    case merge:
      if (edgeVertex->next()->helper()->from()->type == merge)
      {
        insertDiagonal(edgeVertex, edgeVertex->next()->helper());
      }
      t.erase(edgeVertex->next());
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
        if (edgeVertex->next()->helper()->from()->type == merge)
        {
          insertDiagonal(edgeVertex, edgeVertex->next()->helper());
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
          insertDiagonal(edgeVertex, tmpEdge->helper());
        }
        tmpEdge->setHelper(edgeVertex);
      }
      break;
    }
  }
}
