#include "gol-private.h"
#include "gol.h"

void world_copy_data(const struct world * world_in, struct world * world_out)
{
    ASSERT_VALID_WORLD(world_in);
    ASSERT_VALID_WORLD(world_out);

    const unsigned int world_in_width = world_get_width(world_in);
    const unsigned int world_out_width = world_get_width(world_out);
    const unsigned int width = world_in_width <= world_out_width ? world_in_width : world_out_width;

    const unsigned int world_in_height = world_get_height(world_in);
    const unsigned int world_out_height = world_get_height(world_out);
    const unsigned int height = world_in_height <= world_out_height ? world_in_height : world_out_height;

    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const bool cell_is_alive = world_cell_get_is_alive(world_in, x, y);
            world_cell_set_is_alive(world_out, x, y, cell_is_alive);
        }
    }
}
