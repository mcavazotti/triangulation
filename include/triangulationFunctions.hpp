#ifndef TRIANGULATIION_FUNC_H

#define TRIANGULATIION_FUNC_H

#include "halfEdge.hpp"
#include "face.hpp"

void findCorrectEdgeChain(Point *p1, Point *p2, HalfEdge **from, HalfEdge **to);

void insertDiagonal(HalfEdge *fromEdge, HalfEdge *toEdge);

void setFace(HalfEdge *edgeChain, Face *face);

void triangulate();

#endif