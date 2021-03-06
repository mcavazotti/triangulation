#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include "../include/point.hpp"
#include "../include/halfEdge.hpp"

/**
 * Read points from stdin and store them in a DCEL.
 * 
 * It returns a poiter to the highest edge that runs clockwise.
*/
HalfEdge *readDCEL();

/**
 * Write points to stdout in the order they were read.
 * 
 * It uses the Point's and Face's instance array
 */
void printPolygon();

#endif