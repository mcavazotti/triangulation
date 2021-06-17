#include "../include/monotoneFunctions.hpp"
#include "../include/point.hpp"
#include <queue>
#include <vector>
#include <set>
#include <cmath>

#include <stdio.h>
bool edgePointerComparisonFunc(const HalfEdge<int> *a, const HalfEdge<int> *b)
{
  return a < b;
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
  if ((prevVertex->y - vertex->y) * (nextVertex->y - vertex->y) <= 0)
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
  auto diagonal = new HalfEdge<int>(fromEdge->from(),toEdge->from(),fromEdge->twin(),toEdge->prev()->twin(),nullptr);
  fromEdge->twin()->setNext(diagonal);
  toEdge->prev()->twin()->setPrev(diagonal);

  auto diagonalTwin = new HalfEdge<int>(toEdge->from(),fromEdge->from(),toEdge->twin(),fromEdge->prev()->twin(),diagonal);
  diagonal->setTwin(diagonalTwin);
  toEdge->twin()->setNext(diagonalTwin);
  fromEdge->prev()->twin()->setPrev(diagonalTwin);
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
    //TODO: helper() might be null
      if (edgeVertex->prev()->helper()->from()->type == merge)
      {
        insertDiagonal(edgeVertex, edgeVertex->prev()->helper());
      }
      t.erase(edgeVertex->prev());
      break;


    
    }
  }
}
