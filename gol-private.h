#ifndef GOLPRIVATE_H
#define GOLPRIVATE_H

#include <stdbool.h>

struct world
{
    unsigned int width;
    unsigned int height;
    bool ** map;
};

#endif // GOLPRIVATE_H
