#ifndef GOL_H
#define GOL_H

#include <stdbool.h>

struct world;

struct world * world_create(unsigned int width, unsigned int height);
void world_free(struct world * world);
unsigned int world_get_width(const struct world * world);
unsigned int world_get_height(const struct world * world);
bool world_cell_get_is_alive(const struct world * world, unsigned int x, unsigned int y);
void world_cell_set_is_alive(struct world * world, unsigned int x, unsigned int y, bool is_alive);
bool world_cell_is_alive(unsigned int neighbors_count, bool is_alive);
void world_populate(struct world * world, float probability);
void world_update(struct world * world);
void world_print(const struct world * world);
unsigned int world_neighbors_count(struct world * world, unsigned int x, unsigned int y);

#endif // GOL_H
