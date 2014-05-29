#ifndef GOLPRIVATE_H
#define GOLPRIVATE_H

#include <assert.h>
#include <stdbool.h>

#ifdef NDEBUG
#define ASSERT_VALID_WORLD(__WORLD__)
#define ASSERT_VALID_X(__WORLD__, __X__)
#define ASSERT_VALID_Y(__WORLD__, __Y__)
#else
#define ASSERT_VALID_WORLD(__WORLD__) \
    do { \
        const struct world * __world__ = (__WORLD__); \
        assert(__world__ != NULL); \
        assert(__world__->width > 0); \
        assert(__world__->height > 0); \
        assert(__world__->map != NULL); \
        for (unsigned int y = 0; y < __world__->height; ++y) { \
            assert(__world__->map[y] != NULL); \
        } \
    } while (false)

#define ASSERT_VALID_X(__WORLD__, __X__) \
    do { \
        const struct world * __world__ = (__WORLD__); \
        const unsigned int __x__ = (__X__); \
        const unsigned int __world_width__ = world_get_width(__world__); \
        assert(__x__ < __world_width__); \
    } while (false)

#define ASSERT_VALID_Y(__WORLD__, __Y__) \
    do { \
        const struct world * __world__ = (__WORLD__); \
        const unsigned int __y__ = (__Y__); \
        const unsigned int __world_height__ = world_get_height(__world__); \
        assert(__y__ < __world_height__); \
    } while (false)
#endif

struct world
{
    unsigned int width;
    unsigned int height;
    bool ** map;
};

#endif // GOLPRIVATE_H
