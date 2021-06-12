#include "../include/point.hpp"
#include "../include/halfEdge.hpp"
#include "../include/ioFunctions.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
  int numPoints;
  HalfEdge<int> *dcel = readDCEL(&numPoints);

  return 0;
}
