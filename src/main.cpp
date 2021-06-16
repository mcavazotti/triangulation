#include "../include/point.hpp"
#include "../include/halfEdge.hpp"
#include "../include/ioFunctions.hpp"
#include "../include/monotoneFunctions.hpp"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  HalfEdge<int> *dcel = readDCEL();

  // printPolygon();
  makeMonotone(dcel);

  return 0;
}
