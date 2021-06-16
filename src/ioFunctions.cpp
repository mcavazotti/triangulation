#include "../include/ioFunctions.hpp"
#include <iostream>

HalfEdge<int> *readDCEL()
{
  Point<int> *tmpPoint;
  Point<int> *prevPoint = nullptr;

  HalfEdge<int> *tmpEdge;
  HalfEdge<int> *prevEdge = nullptr;
  HalfEdge<int> *firstEdge = nullptr;
  HalfEdge<int> *highestEdge = nullptr;

  HalfEdge<int> *twin = nullptr;
  HalfEdge<int> *prevTwin = nullptr;

  int numPoints;
  std::cin >> numPoints;

  for (int i = 0; i < numPoints; i++)
  {
    int x, y;
    std::cin >> x >> y;
    tmpPoint = new Point<int>(x, y);
    tmpEdge = new HalfEdge<int>(tmpPoint);

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

      twin = new HalfEdge<int>(tmpPoint, prevPoint, nullptr, prevTwin, prevEdge);
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

    twin = new HalfEdge<int>(tmpEdge->to(), tmpEdge->from(), firstEdge->twin(), tmpEdge->prev()->twin(), tmpEdge);
    tmpEdge->prev()->twin()->setPrev(twin);
    tmpEdge->setTwin(twin);

    firstEdge->setPrev(tmpEdge);
    firstEdge->twin()->setNext(tmpEdge->twin());
  }

  // Detect clockwise list
  // Get the other half-edge that starts in the highest point
  HalfEdge<int> *highestTwin = highestEdge->prev()->twin();

  // Calculate if the neighbouring points are on the same side
  // relative to the highest point
  int deltaX1 = highestEdge->to()->x - highestEdge->from()->x;
  int deltaX2 = highestTwin->to()->x - highestTwin->from()->x;

  float slope1, slope2;

  if (deltaX1 * deltaX2 <= 0)
  {
    // Return half-edge that is pointing to the right
    return deltaX1 > deltaX2 ? highestEdge : highestTwin;
  }
  else
  {
    // Return half-edge that has the greatest slope (coeficiente angular)
    slope1 = float(highestEdge->to()->y - highestEdge->from()->y) / float(highestEdge->to()->x - highestEdge->from()->x);
    slope2 = float(highestTwin->to()->y - highestTwin->from()->y) / float(highestTwin->to()->x - highestTwin->from()->x);

    return slope1 > slope2 ? highestEdge : highestTwin;
  }
}

void printPolygon()
{
  std::cout << Point<int>::pointList.size() << "\n";

  for (const auto &p : Point<int>::pointList)
  {
    std::cout << p->x << " " << p->y << "\n";
  }
}