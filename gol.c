#include "gol.h"
#include <stdio.h>
#include "gol-private.h"

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
            const unsigned int height = world_get_height(world);
            for (unsigned int y = 0; y < height; ++y) {
                free(world->map[y]);
            }

            free(world->map);
        }

        free(world);
    }
}

unsigned int world_get_width(const struct world * world)
{
    ASSERT_VALID_WORLD(world);

    return world->width;
}

unsigned int world_get_height(const struct world * world)
{
    ASSERT_VALID_WORLD(world);

    return world->height;
}

bool world_cell_get_is_alive(const struct world * world, unsigned int x, unsigned int y)
{
    ASSERT_VALID_WORLD(world);
    ASSERT_VALID_X(world, x);
    ASSERT_VALID_Y(world, y);

    return world->map[y][x];
}

void world_cell_set_is_alive(struct world * world, unsigned int x, unsigned int y, bool is_alive)
{
    ASSERT_VALID_WORLD(world);
    ASSERT_VALID_X(world, x);
    ASSERT_VALID_Y(world, y);

    world->map[y][x] = is_alive;
}

bool world_cell_is_alive(unsigned int neighbors_count, bool is_alive)
{
    // Rappel des règles :
    // - une cellule vivante meurt si elle a moins de deux ou plus de trois
    //   voisins
    // - une cellule morte nait si elle a trois voisins
    // - une cellule ne change pas d'état dans les autres cas

        if (neighbors_count > 3) { // Trop de voisins
            return false;
        }

        return true;
    } else {
        if (neighbors_count == 3) { // Copulation
            return true;
        }

        return false;
    }
}

void world_populate(struct world * world, float probability)
{
    ASSERT_VALID_WORLD(world);

    const unsigned int width = world_get_width(world);
    const unsigned int height = world_get_height(world);
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            world->map[y][x] = (((float) rand()) / ((float) RAND_MAX)) <= probability;
        }
    }
}

void world_update(struct world * world)
{
    ASSERT_VALID_WORLD(world);

    // Création d'un monde temporaire qui stockera la nouvelle génération
    struct world * world_tmp = world_create(world->width, world->height);

    // Calcul de la génération suivante
    const unsigned int width = world_get_width(world);
    const unsigned int height = world_get_height(world);
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const unsigned int neighbors_count = world_neighbors_count(world, x, y);
            const bool is_alive = world_cell_get_is_alive(world, x, y);
            const bool new_is_alive = world_cell_is_alive(neighbors_count, is_alive);
            world_cell_set_is_alive(world_tmp, x, y, new_is_alive);
        }
    }

    // Copie des données
    world_copy_data(world_tmp, world);

    // Ménage
    world_free(world_tmp);
}

void world_print(const struct world * world)
{
    ASSERT_VALID_WORLD(world);

    const unsigned int width = world_get_width(world);
    const unsigned int height = world_get_height(world);
    for (unsigned int y = 0; y < height; ++y) {
        for (unsigned int x = 0; x < width; ++x) {
            const bool cell_is_alive = world_cell_get_is_alive(world, x, y);
            printf("%c", (cell_is_alive ? 'X' : '.'));
        }
        printf("\n");
    }
    printf("\n");
}

unsigned int world_neighbors_count(struct world * world, unsigned int x, unsigned int y)
{
    unsigned int neighbors_count = 0;

    const unsigned int width = world_get_width(world);
    const unsigned int height = world_get_height(world);

    const unsigned left = (x == 0) ? (width - 1) : (x - 1);
    const unsigned right = (x == width - 1) ? 0 : x + 1;
    const unsigned bottom = (y == 0) ? (height - 1) : (y - 1);
    const unsigned top = (y == height - 1) ? 0 : y + 1;

    if (world_cell_get_is_alive(world, x, top)) { // Haut
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, x, bottom)) { // Bas
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, left, y)) { // Gauche
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, right, y)) { // Droite
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, left, top)) { // Haut gauche
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, right, top)) { // Haut droit
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, left, bottom)) { // Bas gauche
        ++neighbors_count;
    }

    if (world_cell_get_is_alive(world, right, bottom)) { // Bas droit
        ++neighbors_count;
    }

    return neighbors_count;
}
