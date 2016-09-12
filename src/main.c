#include <stdio.h>

#include "world.h"
#include "ui.h"

int main(int argc, char **argv) {

  WorldParams worldParams;
  worldParams.Nx = 1024 + 1;
  worldParams.Ny = 1024 + 1;
  worldParams.Nz = 100;

  printf("Building world..."); fflush(stdout);
  world_init(&worldParams);
  world_genTerrain();
  printf(" done.\n");

  ui_eventLoop();

  printf("Tearing down world..."); fflush(stdout);
  world_destroy();
  printf(" done.\n");

  return 0;
}
