#include <stdlib.h>

#include "world.h"

Voxel *getVoxel(int x, int y, int z) {
  return &(world.voxels[z*world.params->Nx*world.params->Ny
                        + y*world.params->Nx
                        + x]);
}

void world_init(WorldParams *worldParams) {

  int nVoxels = worldParams->Nx * worldParams->Ny * worldParams->Nz;
  world.voxels = malloc(sizeof(Voxel)*nVoxels);
  world.params = worldParams;
}

void world_setTerrainHeight(int x, int y, int height) {
  for (int z=0; z<height; z++)
    getVoxel(x, y, z)->dirt = 1;

  for (int z=height; z<world.params->Nz; z++)
    getVoxel(x, y, z)->dirt = 0;
}

void world_genTerrain() {

}

void world_destroy() {
  free(world.voxels);
}
