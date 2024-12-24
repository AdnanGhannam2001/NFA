#include "nfa.h"

ARRAY_IMPL(state_array, state_t)

static bool state_array_contains(state_array_t *, const char *, size_t);
static int nfa_state_free(void *const _, struct hashmap_element_s *const);

nfa_t nfa_init(state_t starting_state)
{
    hashmap_t hashmap;
    hashmap_create(8, &hashmap);

    nfa_t nfa = (nfa_t)
    {
        .states = hashmap,
        .starting_state = starting_state,
        .ending_states = state_array_init(),
    };

    nfa_add(&nfa, starting_state, false);

    return nfa;
}

void nfa_add(nfa_t *nfa, state_t state, bool is_ending)
{
    state_t *s = (state_t *)malloc(sizeof(state_t));
    memcpy(s, &state, sizeof(state_t));
    hashmap_put(&nfa->states, state.name, (hashmap_uint32_t)strlen(state.name), s);

    if (is_ending)
    {
        state_array_push(&nfa->ending_states, state);
    }
}

static bool state_array_contains(state_array_t *state_array, const char *name, size_t len)
{
    for (size_t i = 0; i < state_array->count; ++i)
    {
        if (strncmp(state_array->items[i].name, name, len) == 0)
        {
            return true;
        }
    }

    return false;
}

static int nfa_state_free(UNUSED void *const _, struct hashmap_element_s *const element)
{
    free(element->data);
    return 0;
}

bool nfa_process(nfa_t *nfa, const char *string)
{
    transition_stack_t stack = {0};

    transition_stack_push(&stack, (nfa_transition_t){ .position = 0, .current = &nfa->starting_state });

    while (!transition_stack_empty(&stack))
    {
        nfa_transition_t transition = transition_stack_pop(&stack);
        if (state_array_contains(&nfa->ending_states, transition.current->name, transition.current->len))
        {
            return true;
        }

        const char input = string[transition.position];

        for (int i = (int)transition.current->transactions.count - 1; i >= 0; --i)
        {
            state_transition_t *s_transition = &transition.current->transactions.items[i];
            if (matcher_matches(s_transition->matcher, input))
            {
                transition_stack_push(&stack,
                    (nfa_transition_t)
                    {
                        .position = transition.position + (MATCHER_TYPE(s_transition->matcher) == MATCHER_EPSILON ? 0 : 1),
                        .current = s_transition->next
                    });
            }
        }
    }

    return false;
}

void nfa_free(nfa_t *nfa)
{
    hashmap_iterate_pairs(&nfa->states, &nfa_state_free, NULL);
    hashmap_destroy(&nfa->states);
}

nfa_transition_t transition_stack_top(const transition_stack_t *transition_stack)
{
    if (transition_stack->count == 0)
    {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }

    return transition_stack->items[transition_stack->count - 1];
}

void transition_stack_push(transition_stack_t *transition_stack, nfa_transition_t transition)
{
    transition_stack->items[transition_stack->count++] = transition;
}

nfa_transition_t transition_stack_pop(transition_stack_t *transition_stack)
{
    if (transition_stack->count == 0)
    {
        fprintf(stderr, "Stack is empty\n");
        exit(1);
    }

    return transition_stack->items[--transition_stack->count];
}

bool transition_stack_empty(const transition_stack_t *transition_stack)
{
    return transition_stack->count == 0;
}

void transition_stack_print(const transition_stack_t *transition_stack)
{
    for (size_t i = 0; i < transition_stack->count; ++i)
    {
        state_print(transition_stack->items[i].current);
    }
}

void transition_stack_clear(transition_stack_t *transition_stack)
{
    memset(transition_stack->items, 0, RE_TRANSITION_STACK_SIZE);
    transition_stack->count = 0;
}
