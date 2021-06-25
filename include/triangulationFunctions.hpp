#ifndef TRIANGULATIION_FUNC_H

#define TRIANGULATIION_FUNC_H

#include "halfEdge.hpp"
#include "face.hpp"

/**
 * Search through Face::faceList the face in which its half-edges contain the given points.
 * 
 * It writes in "from" and "to" the reference to those half-edges.
*/
void findCorrectEdgeChain(Point *p1, Point *p2, HalfEdge **from, HalfEdge **to);


/**
 * Insert a diagonal and partition the face.
*/
void insertDiagonal(HalfEdge *fromEdge, HalfEdge *toEdge);

/**
 * Set the face reference in each node of the edge chain. 
*/
void setFace(HalfEdge *edgeChain, Face *face);


/**
 * Triangulate the monotone faces stored in Face::faceList
 */
void triangulate();

#endif