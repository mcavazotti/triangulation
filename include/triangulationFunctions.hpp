#ifndef TRIANGULATIION_FUNC_H

#define TRIANGULATIION_FUNC_H

#include "halfEdge.hpp"
#include "face.hpp"

void insertDiagonal(HalfEdge *fromEdge, HalfEdge *toEdge);

void setFace(HalfEdge *edgeChain, Face *face);

#endif