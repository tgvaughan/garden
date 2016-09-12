#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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

  for (int i=0; i<nVoxels; i++) {
    world.voxels[i].dirt = 0;
    world.voxels[i].water = 0;
  }
}

void setTerrainHeight(int x, int y, int height) {
  for (int z=0; z<height; z++)
    getVoxel(x, y, z)->dirt = 1;

  for (int z=height; z<world.params->Nz; z++)
    getVoxel(x, y, z)->dirt = 0;
}

double getNoiseMag(int disp, double amp, double exponent) {
  return(amp*pow(disp,exponent));
}

/**
 * Use Diamond-Square algorithm to generate terrain.
 *
 * Note: Assumes square grid!
 */
void world_genTerrain() {


  double noiseAmp = 0.1;
  double noiseExp = 1.0;

  int N = world.params->Nx;

  double heightMap[N][N];

  printf("Hey.\n");

  heightMap[0][0] = 0.5;
  heightMap[0][N-1] = 0.5;
  heightMap[N-1][0] = 0.5;
  heightMap[N-1][N-1] = 0.5;

  int l = N - 1;

  while(1) {

    if (l<1)
      break;

    printf("Generating terrain at resolution %d\n",l);

    printf("Diamonds... ");

    for (int x0=0; x0<N-1; x0 += l) {
      for (int y0=0; y0<N-1; y0 += l) {

        int x1 = x0 + l;
        int y1 = y0 + l;
        int cx = x0 + (l/2);
        int cy = y0 + (l/2);

        double cHeight = 0.25*(heightMap[x0][x0] + heightMap[x0][y1]
                               + heightMap[x1][y0] + heightMap[x1][y1]);

        double noiseMag = getNoiseMag(l/(double)N, noiseAmp, noiseExp);

        heightMap[cx][cy] = cHeight + noiseMag*(drand48()-0.5);
      }
    }

    if (l/2 < 1)
      break;

    printf("Squares...");

    for (int yc=0; yc<N; yc += l/2) {
      int offset = (((yc-1)/(l/2) + 1)%2)*(l/2);
      for (int xc=offset; xc<N; xc += l) {

        double cHeight = 0;
        int sides = 0;

        if (xc-l/2 >= 0) {
          cHeight = cHeight + heightMap[xc-l/2][yc];
          sides += 1;
        }

        if (xc+l/2 <= N-1) {
          cHeight = cHeight + heightMap[xc+l/2][yc];
          sides += 1;
        }

        if (yc-l/2 >= 0) {
          cHeight = cHeight + heightMap[xc][yc-l/2];
          sides += 1;
        }

        if (yc+l/2 <= N-1) {
          cHeight = cHeight + heightMap[xc][yc+l/2];
          sides += 1;
        }

        cHeight /= sides;

        double noiseMag = getNoiseMag(0.5*l/(double)N, noiseAmp, noiseExp);
        heightMap[xc][yc] = cHeight + noiseMag*(drand48()-0.5);
      }
    }

    l /= 2;
  }

  for (int x=0; x<N; x++) {
    for (int y=0; y<N; y++) {
      setTerrainHeight(x, y, (int)(world.params->Nz*heightMap[x][y]));
    }
  }
}

void world_destroy() {
  free(world.voxels);
}
