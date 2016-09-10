#include "world.h"
#include "ui.h"

int main(int argc, char **argv) {

  WorldParams worldParams;
  worldParams.Nx = 1000;
  worldParams.Ny = 1000;
  worldParams.Nz = 100;
  world_init(&worldParams);

  ui_eventLoop();

  world_destroy();

  return 0;
}
