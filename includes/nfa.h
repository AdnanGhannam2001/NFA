#ifndef RE_NFA_H
#define RE_NFA_H

#include "common.h"
#include "state.h"
#include "array.h"
#include "hashmap.h"

ARRAY(state_array, state_t)

typedef struct nfa
{
    hashmap_t states;
    state_t starting_state;
    state_array_t ending_states;
} nfa_t;

nfa_t nfa_init(state_t starting_state);
void nfa_add(nfa_t *, state_t, bool is_ending);
bool nfa_process(nfa_t *, const char*);
void nfa_free(nfa_t *);

typedef struct nfa_transition
{
    size_t position;
    state_t *current;
} nfa_transition_t;

#ifndef RE_TRANSITION_STACK_SIZE
#define RE_TRANSITION_STACK_SIZE __UINT8_MAX__ * 16
#endif // RE_TRANSITION_STACK_SIZE

typedef struct transition_stack
{
    nfa_transition_t items[RE_TRANSITION_STACK_SIZE];
    size_t count;
} transition_stack_t;

nfa_transition_t transition_stack_top(const transition_stack_t *);
void transition_stack_push(transition_stack_t *, nfa_transition_t);
nfa_transition_t transition_stack_pop(transition_stack_t *);
bool transition_stack_empty(const transition_stack_t *);
void transition_stack_print(const transition_stack_t *);
void transition_stack_clear(transition_stack_t *);

#endif // RE_NFA_H
