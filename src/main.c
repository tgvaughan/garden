#include "world.h"
#include "ui.h"

int main(int argc, char **argv) {

  WorldParams worldParams;
  worldParams.Nx = 1024 + 1;
  worldParams.Ny = 1024 + 1;
  worldParams.Nz = 100;
  world_init(&worldParams);
  world_genTerrain();

  ui_eventLoop();

  world_destroy();

  return 0;
}
