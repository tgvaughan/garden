typedef struct {
  int Nx, Ny, Nz;
} WorldParams;

typedef struct {
  int dirt;
  int water;
} Voxel;

struct {
  Voxel *voxels;
  WorldParams *params;
} world;

void world_init(WorldParams *);
void world_genTerrain();
void world_destroy();
