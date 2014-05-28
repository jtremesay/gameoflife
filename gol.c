#include "gol.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "gol-private.h"

#ifdef NDEBUG
#define ASSERT_VALID_WORLD(__WORLD__)
#else
#define ASSERT_VALID_WORLD(__WORLD__) \
do { \
    struct world * __world__ = (__WORLD__); \
    assert(__world__ != NULL); \
    assert(__world__->width > 0); \
    assert(__world__->height > 0); \
    assert(__world__->map != NULL); \
    for (unsigned int y = 0; y < __world__->height; ++y) { \
        assert(__world__->map[y] != NULL); \
    } \
} while (false)
#endif

struct world * world_create(unsigned int width, unsigned int height)
{
    if (width <= 0 || height <= 0) {
        return NULL;
    }

    struct world * world = malloc(sizeof(struct world));
    if (!world) {
        goto error;
    }

    world->width = width;
    world->height = height;

    world->map = calloc(height, sizeof(bool *));
    if (!world->map) {
        goto error;
    }

    for (unsigned int y = 0; y < world->height; ++y) {
        world->map[y] = calloc(width, sizeof(bool));
        if (!world->map[y]) {
            goto error;
        }
    }

    return world;

error:
    world_free(world);

    return NULL;
}

void world_free(struct world * world)
{
    if (world) {
        if (world->map) {
            for (unsigned int y = 0; y < world->height; ++y) {
                if (world->map[y]) {
                    free(world->map[y]);
                }
            }

            free(world->map);
        }

        free(world);
    }
}

void world_populate(struct world * world, float probability)
{
    ASSERT_VALID_WORLD(world);

    for (unsigned int y = 0; y < world->height; ++y) {
        for (unsigned int x = 0; x < world->width; ++x) {
            world->map[y][x] = (((float) rand()) / ((float) RAND_MAX)) <= probability;
        }
    }
}

void world_update(struct world * world)
{
    ASSERT_VALID_WORLD(world);

    struct world * world_tmp = world_create(world->width, world->height);

    for (unsigned int y = 0; y < world->height; ++y) {
        for (unsigned int x = 0; x < world->width; ++x) {
           const unsigned int number_of_neighboors = world_number_of_neighboors(world, x, y);

        }
    }

    world_free(world_tmp);
}

void world_print(struct world * world)
{
    ASSERT_VALID_WORLD(world);

    for (unsigned int y = 0; y < world->height; ++y) {
        for (unsigned int x = 0; x < world->width; ++x) {
            printf("%c", (world->map[y][x] ? 'X' : '.'));
        }
        printf("\n");
    }
    printf("\n");
}

unsigned int world_number_of_neighboors(struct world * world, unsigned int x, unsigned int y)
{
    return 0;
}
