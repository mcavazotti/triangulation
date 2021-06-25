#ifndef FACE_H

#define FACE_H
#include "halfEdge.hpp"

class HalfEdge;

/**
 * This class represents of a face or partition.
 * 
 * It has an internal counter and a static array that stores every Face instance
*/
class Face
{
public:
  Face() : eC(nullptr)
  {
    id = counter;
    counter++;
    faceList.push_back(this);
  }

  int getId() const { return id; }
  HalfEdge *edgeChain() const { return eC; }

  void setChain(HalfEdge *e)
  {
    eC = e;
  }

  int getFaceSize()
  {
    HalfEdge *tmp = eC;
    int numPoints = 0;

    do
    {
      numPoints++;
      tmp = tmp->next();
    } while (tmp != eC);
    return numPoints;
  }

public:
  static std::vector<Face *> faceList;

private:
  HalfEdge *eC;
  int id;
  static int counter;
};
inline int Face::counter = 1;
inline std::vector<Face *> Face::faceList = std::vector<Face *>();

#endif