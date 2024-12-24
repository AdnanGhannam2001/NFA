#ifndef RE_STATE_H
#define RE_STATE_H

#include "array.h"
#include "matcher.h"

typedef struct state state_t;

typedef struct state_transition
{
    matcher_t *matcher;
    state_t *next;
} state_transition_t;

ARRAY(state_transition_array, state_transition_t)

struct state
{
    const char *name;
    size_t len;
    state_transition_array_t transactions;
};

state_t state_init(const char *, size_t);
void state_add_transition(state_t *, state_t *, matcher_t *);
void state_print(const state_t *);
void state_free(state_t *);

#endif // RE_STATE_H
