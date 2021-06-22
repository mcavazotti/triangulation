#ifndef FACE_H

#define FACE_H
#include "halfEdge.hpp"

class HalfEdge;

class Face
{
public:
  Face() : edgeChain(nullptr)
  {
    id = counter;
    counter++;
  }

  int getId() const { return id; }
  HalfEdge *getChain() const { return edgeChain; }

  void setChain(HalfEdge *e)
  {
    edgeChain = e;
  }

#ifdef DEBUG
  Point getMiddlePoint()
  {
    Point p = Point();
    int numPoints = 0;
    HalfEdge *tmp = edgeChain;

    do
    {
      p.x += tmp->from()->x;
      p.y += tmp->from()->y;
      numPoints++;
      tmp = tmp->next();
    } while (tmp != edgeChain);
    return Point(p.x / numPoints, p.y / numPoints);
  }
#endif

public:
  static std::vector<Face *> faceList;

private:
  HalfEdge *edgeChain;
  int id;
  static int counter;
};
inline int Face::counter = 1;
inline std::vector<Face *> Face::faceList = std::vector<Face *>();

#endif