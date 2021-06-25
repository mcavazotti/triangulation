#include "../include/triangulationFunctions.hpp"
#include "../include/face.hpp"
#include "../include/halfEdge.hpp"
#include "../include/utilFunctions.hpp"
#include <vector>
#include <stack>
#include <algorithm>

#ifdef DEBUG
#include <stdio.h>
#endif

void findCorrectEdgeChain(Point *p1, Point *p2, HalfEdge **from, HalfEdge **to)
{
  HalfEdge *tmp, *t, *f;
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
}

void setFace(HalfEdge *edgeChain, Face *face)
{
#ifdef DEBUG
  // fprintf(stderr, "\nsetFace\n");
//   fprintf(stderr, "\n\n#######\n");
//   fprintf(stderr, "setFace\n");
//   fprintf(stderr, "#######\n");
#endif
  HalfEdge *tmp, *highest;

  tmp = edgeChain;
  highest = edgeChain;

  // #ifdef DEBUG
  //   fprintf(stderr, "%d %d [%lx]\n", tmp->from()->x, tmp->from()->y, (long int)tmp);
  // #endif
  do
  {
    tmp->setFace(face);
    if ((*tmp) > (*highest))
      highest = tmp;

    tmp = tmp->next();
    // #ifdef DEBUG
    //     fprintf(stderr, "%d %d [%lx]\n", tmp->from()->x, tmp->from()->y, (long int)tmp);
    // #endif
  } while (tmp != edgeChain);
  if (face != nullptr)
    face->setChain(highest);

  // #ifdef DEBUG
  //   fprintf(stderr, "EXIT setFace\n");
  // #endif
}

void insertDiagonal(HalfEdge *fromEdge, HalfEdge *toEdge)
{
  // #ifdef DEBUG
  //   fprintf(stderr, "\n#############\n");
  //   fprintf(stderr, "insertDiagonal\n");
  //   fprintf(stderr, "#############\n");
  //   fprintf(stderr, "%d %d [%lx]\n", fromEdge->from()->x, fromEdge->from()->y, (long int)fromEdge);
  //   fprintf(stderr, "%d %d [%lx]\n", toEdge->from()->x, toEdge->from()->y, (long int)toEdge);
  // #endif
  auto diagonal = new HalfEdge(toEdge->from(), fromEdge->from(), toEdge->prev(), fromEdge, nullptr);
#ifdef DEBUG
  diagonal->insertedAfter = 1;
#endif

  auto diagonalTwin = new HalfEdge(fromEdge->from(), toEdge->from(), fromEdge->prev(), toEdge, diagonal);
#ifdef DEBUG
  diagonalTwin->insertedAfter = 1;
#endif

  diagonal->setTwin(diagonalTwin);
  fromEdge->prev()->setNext(diagonalTwin);
  toEdge->prev()->setNext(diagonal);

  toEdge->setPrev(diagonalTwin);
  fromEdge->setPrev(diagonal);

  diagonal->setHelper(diagonal);
  diagonalTwin->setHelper(diagonalTwin);

  setFace(diagonal, fromEdge->face());
  setFace(diagonalTwin, new Face());
}

void triangulate()
{
  std::vector<Face *> faces(Face::faceList);
  std::vector<HalfEdge *> v;
  std::stack<HalfEdge *> s;
  HalfEdge *topEdge, *tmpEdge, *pivot, *fromEdge, *toEdge;

  for (auto &face : faces)
  {
    v.clear();
    s = std::stack<HalfEdge *>();
    tmpEdge = face->edgeChain();

    // Fill vector and label chains
    do
    {
      v.push_back(tmpEdge);
      if ((*tmpEdge) > (*tmpEdge->prev()))
      {
        tmpEdge->chain = 1;
      }
      else
      {
        tmpEdge->chain = 2;
      }
      tmpEdge = tmpEdge->next();
    } while (tmpEdge != face->edgeChain());

    std::sort(v.begin(), v.end(), edgePointerVerticalComparisonFunc);

    s.push(v[0]);
    s.push(v[1]);

    for (int i = 2; i < v.size() - 1; i++)
    {
      topEdge = s.top();
      if (v[i]->chain != s.top()->chain)
      {
        while (!s.empty())
        {
          tmpEdge = s.top();
          s.pop();
          if (s.size())
          {
            findCorrectEdgeChain(v[i]->from(),tmpEdge->from(),&fromEdge, &toEdge);
            insertDiagonal(fromEdge, toEdge);
          }
        }
        s.push(v[i - 1]);
        s.push(v[i]);
      }
      else
      {
        pivot = s.top();
        s.pop();
        while (!s.empty())
        {
          tmpEdge = s.top();
          s.pop();
          auto angle = computeAngle(v[i]->from(), pivot->from(), tmpEdge->from());
          HalfEdge *leftVertex = edgePointerHorizontalComparisonFunc(pivot, tmpEdge) ? tmpEdge : v[i];
          if ((*leftVertex) > (*pivot))
          {
            angle = -angle;
          }
          if (angle > 0)
          {
            s.push(tmpEdge);
            tmpEdge = pivot;
            break;
          }
          else
          {
            findCorrectEdgeChain(v[i]->from(), tmpEdge->from(), &fromEdge, &toEdge);
            insertDiagonal(fromEdge, toEdge);
            pivot = tmpEdge;
          }
        }
        if (s.empty() || s.top() != tmpEdge)
        {
          s.push(tmpEdge);
        }
        s.push(v[i]);
      }
    }
    s.pop();
    while (s.size() > 1)
    {
      findCorrectEdgeChain(v.back()->from(), s.top()->from(), &fromEdge, &toEdge);
      insertDiagonal(fromEdge, toEdge);
      s.pop();
    }
  }
}