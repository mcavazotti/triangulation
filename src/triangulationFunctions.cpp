#include "../include/triangulationFunctions.hpp"

#ifdef DEBUG
#include <stdio.h>
#endif

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
