#include "../include/point.hpp"
#include "../include/halfEdge.hpp"
#include "../include/ioFunctions.hpp"
#include "../include/monotoneFunctions.hpp"
#include <stdio.h>

int main(int argc, char const *argv[])
{
  HalfEdge *dcel = readDCEL();

  makeMonotone(dcel);
  printPolygon();

  return 0;
}
