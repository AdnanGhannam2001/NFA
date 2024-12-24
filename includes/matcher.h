#ifndef RE_MATCHER_H
#define RE_MATCHER_H

#include "common.h"

typedef enum matcher_type
{
    MATCHER_CHAR,
    MATCHER_EPSILON,
} matcher_type_t;

typedef struct matcher
{
    matcher_type_t type;
} matcher_t;

typedef struct matcher_char
{
    matcher_t matcher;
    const char c;
} matcher_char_t;

#define MATCHER_TYPE(matcher) ((matcher)->type)
#define AS_MATCHER_CHAR(matcher) ((matcher_char_t*) matcher)

bool matcher_matches(matcher_t *, const char);
void matcher_print(matcher_t *);

matcher_t matcher_new(matcher_type_t);
matcher_char_t matcher_char_new(const char c);
matcher_t matcher_epsilon_new();

#endif // RE_MATCHER_H
