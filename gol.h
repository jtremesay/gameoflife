#ifndef GOL_H
#define GOL_H

struct world;

struct world * world_create(unsigned int width, unsigned int height);
void world_free(struct world * world);
unsigned int world_get_width(const struct world * world);
unsigned int world_get_height(const struct world * world);
void world_populate(struct world * world, float probability);
void world_update(struct world * world);
void world_print(const struct world * world);
unsigned int world_number_of_neighboors(struct world * world, unsigned int x, unsigned int y);

#endif // GOL_H
