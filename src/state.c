#include "state.h"

ARRAY_IMPL(state_transition_array, state_transition_t)

state_t state_init(const char* name, size_t len)
{
    return (state_t)
    {
        .name = name,
        .len = len,
        .transactions = state_transition_array_init(),
    };
}

void state_add_transition(state_t *from, state_t *to, matcher_t *matcher)
{
    state_transition_t transition = (state_transition_t){ .matcher = matcher, .next = to };
    state_transition_array_push(&from->transactions, transition);
}

void state_print(UNUSED const state_t *state)
{
    NOT_IMPLEMENTED;
}

void state_free(state_t *state)
{
    state_transition_array_free(&state->transactions);
}
