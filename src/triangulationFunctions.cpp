#include "../include/triangulationFunctions.hpp"

void insertDiagonal(HalfEdge *fromEdge, HalfEdge *toEdge)
{
  auto diagonal = new HalfEdge(fromEdge->from(), toEdge->from(), fromEdge->twin(), toEdge->prev()->twin(), nullptr);
#ifdef DEBUG
  diagonal->insertedAfter = 1;
#endif
  fromEdge->twin()->setNext(diagonal);
  toEdge->prev()->twin()->setPrev(diagonal);

  auto diagonalTwin = new HalfEdge(toEdge->from(), fromEdge->from(), toEdge->twin(), fromEdge->prev()->twin(), diagonal);
#ifdef DEBUG
  diagonalTwin->insertedAfter = 1;
#endif
  diagonal->setTwin(diagonalTwin);
  toEdge->twin()->setNext(diagonalTwin);
  fromEdge->prev()->twin()->setPrev(diagonalTwin);
}

void setFace(HalfEdge *edgeChain, Face *face)
{
  HalfEdge *tmp, *highest;

  tmp = edgeChain;
  highest = edgeChain;

  do
  {
    tmp->setFace(face);
    if ((*tmp) > (*highest))
      highest = tmp;

    tmp = tmp->next();
  } while (tmp != edgeChain);
  if (face != nullptr)
    face->setChain(highest);
}