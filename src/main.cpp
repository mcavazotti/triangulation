#include "../include/halfEdge.hpp"
#include "../include/ioFunctions.hpp"
#include "../include/monotoneFunctions.hpp"
#include "../include/triangulationFunctions.hpp"

int main(int argc, char const *argv[])
{
  HalfEdge *dcel = readDCEL();

  makeMonotone(dcel);
  triangulate();
  printPolygon();

  return 0;
}
