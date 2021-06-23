#include "../include/ioFunctions.hpp"
#include "../include/triangulationFunctions.hpp"
#include "../include/face.hpp"
#include <iostream>

HalfEdge *readDCEL()
{
  Point *tmpPoint;
  Point *prevPoint = nullptr;

  HalfEdge *tmpEdge;
  HalfEdge *prevEdge = nullptr;
  HalfEdge *firstEdge = nullptr;
  HalfEdge *highestEdge = nullptr;

  HalfEdge *twin = nullptr;
  HalfEdge *prevTwin = nullptr;

  int numPoints;
  std::cin >> numPoints;

  for (int i = 0; i < numPoints; i++)
  {
    int x, y;
    std::cin >> x >> y;
    tmpPoint = new Point(x, y);
    tmpEdge = new HalfEdge(tmpPoint);

    if (firstEdge == nullptr)
    {
      firstEdge = tmpEdge;
    }

    // Record highest edge to find clockwise list
    if (highestEdge == nullptr || *(tmpPoint) > *(highestEdge->from()))
    {
      highestEdge = tmpEdge;
    }

    if (prevEdge != nullptr)
    {
      //Link edges
      prevEdge->setTo(tmpPoint);
      tmpEdge->setPrev(prevEdge);
      prevEdge->setNext(tmpEdge);

      // Handle twin half-edges
      if (prevEdge->prev() != nullptr)
      {
        prevTwin = prevEdge->prev()->twin();
      }

      twin = new HalfEdge(tmpPoint, prevPoint, nullptr, prevTwin, prevEdge);
      if (prevTwin != nullptr)
      {
        prevTwin->setPrev(twin);
      }
      prevEdge->setTwin(twin);
    }

    prevEdge = tmpEdge;
    prevPoint = tmpPoint;
  }

  // Tie first and last edges
  if (numPoints >= 3)
  {
    tmpEdge->setTo(firstEdge->from());
    tmpEdge->setNext(firstEdge);

    twin = new HalfEdge(tmpEdge->to(), tmpEdge->from(), firstEdge->twin(), tmpEdge->prev()->twin(), tmpEdge);
    tmpEdge->prev()->twin()->setPrev(twin);
    tmpEdge->setTwin(twin);

    firstEdge->setPrev(tmpEdge);
    firstEdge->twin()->setNext(tmpEdge->twin());
  }

  // Detect clockwise list
  // Get the other half-edge that starts in the highest point
  HalfEdge *highestTwin = highestEdge->prev()->twin();

  // Calculate if the neighbouring points are on the same side
  // relative to the highest point
  int deltaX1 = highestEdge->to()->x - highestEdge->from()->x;
  int deltaX2 = highestTwin->to()->x - highestTwin->from()->x;

  float slope1, slope2;

  if (deltaX1 * deltaX2 <= 0)
  {
    // Return half-edge that is pointing to the left
    if (deltaX1 > deltaX2)
    {
      setFace(highestEdge, nullptr);
      setFace(highestTwin, new Face());
      return highestEdge;
    }
    else
    {
      setFace(highestTwin, nullptr);
      setFace(highestEdge, new Face());
      return highestTwin;
    }
  }
  else
  {
    // Return half-edge that has the smallest slope (coeficiente angular)
    slope1 = float(highestEdge->to()->y - highestEdge->from()->y) / float(highestEdge->to()->x - highestEdge->from()->x);
    slope2 = float(highestTwin->to()->y - highestTwin->from()->y) / float(highestTwin->to()->x - highestTwin->from()->x);

    if (slope1 > slope2)
    {
      setFace(highestEdge, nullptr);
      setFace(highestTwin, new Face());
      return highestEdge;
    }
    else
    {
      setFace(highestTwin, nullptr);
      setFace(highestEdge, new Face());
      return highestTwin;
    }
  }
}

void printPolygon()
{
#ifdef DEBUG
  std::cout << Face::faceList.size() << "\n";
  for (const auto &f : Face::faceList)
  {
    // std::cerr << "\n" << f->getId() << "\n";
    std::cout << f->getFaceSize() << "\n";
    HalfEdge *tmp = f->edgeChain();
    do
    {
      std::cout << tmp->from()->x << " " << tmp->from()->y << "\n";
      tmp = tmp->next();
    } while (tmp != f->edgeChain());
  }

  std::cout << HalfEdge::edgeList.size() << "\n";

  for (const auto &e : HalfEdge::edgeList)
  {
    std::cout << e->from()->x << " " << e->from()->y << " " << e->to()->x << " " << e->to()->y << " " << e->from()->type << " " << e->insertedAfter << "\n";
  }

#else
  std::cout << Point::pointList.size() << "\n";

  for (const auto &p : Point::pointList)
  {
    std::cout << p->x << " " << p->y << "\n";
  }
#endif
}