#ifndef RE_ARRAY_H
#define RE_ARRAY_H

#include "common.h"

typedef size_t array_size_t;

#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

#define ARRAY(name, type)                          \
    typedef struct                                 \
    {                                              \
        type *items;                               \
        array_size_t count;                        \
        array_size_t capacity;                     \
    } name##_t;                                    \
    name##_t name##_init();                        \
    void name##_push(name##_t *array, type value); \
    void name##_free(name##_t *array);

#define ARRAY_IMPL(name, type)                                                                    \
    name##_t name##_init()                                                                        \
    {                                                                                             \
        return (name##_t){                                                                        \
            .items = NULL,                                                                        \
            .count = 0,                                                                           \
            .capacity = 0,                                                                        \
        };                                                                                        \
    }                                                                                             \
    void name##_push(name##_t *array, type value)                                                 \
    {                                                                                             \
        if ((array)->count >= (array)->capacity)                                                  \
        {                                                                                         \
            (array)->capacity = GROW_CAPACITY((array)->capacity);                                 \
            (array)->items = (type *)realloc((array)->items, ((array)->capacity * sizeof(type))); \
        }                                                                                         \
        (array)->items[(array)->count] = (value);                                                 \
        (array)->count++;                                                                         \
    }                                                                                             \
    void name##_free(name##_t *array)                                                             \
    {                                                                                             \
        free((array)->items);                                                                     \
        *array = name##_init();                                                                   \
    }

#endif // RE_ARRAY_H
