#include "nfa.h"

void example1()
{
    state_t q0 = state_init("q0", strlen("q0")),
            q1 = state_init("q1", strlen("q1")),
            q2 = state_init("q2", strlen("q2")),
            q3 = state_init("q3", strlen("q3"));

    matcher_char_t matcher_a = matcher_char_new('a');
    matcher_char_t matcher_b = matcher_char_new('b');
    matcher_t matcher_ep = matcher_epsilon_new();

    state_add_transition(&q0, &q1, (matcher_t *)&matcher_a);
    state_add_transition(&q1, &q2, (matcher_t *)&matcher_b);
    state_add_transition(&q2, &q2, (matcher_t *)&matcher_b);
    state_add_transition(&q2, &q3, &matcher_ep);

    nfa_t nfa = nfa_init(q0);
    nfa_add(&nfa, q1, false);
    nfa_add(&nfa, q2, false);
    nfa_add(&nfa, q3, true);

    printf("%d\n", nfa_process(&nfa, "abbbbbb"));
    printf("%d\n", nfa_process(&nfa, "aabbbbbb"));
    printf("%d\n", nfa_process(&nfa, "ab"));
    printf("%d\n", nfa_process(&nfa, "a"));
    printf("\n");

    state_free(&q0);
    state_free(&q1);
    state_free(&q2);
    state_free(&q3);

    nfa_free(&nfa);
}

void example2()
{
    state_t q0 = state_init("q0", strlen("q0")),
            q1 = state_init("q1", strlen("q1")),
            q2 = state_init("q2", strlen("q2"));

    matcher_char_t matcher_a = matcher_char_new('a');
    matcher_char_t matcher_b = matcher_char_new('b');
    matcher_t matcher_ep = matcher_epsilon_new();

    state_add_transition(&q0, &q1, (matcher_t *)&matcher_a);
    state_add_transition(&q1, &q1, (matcher_t *)&matcher_ep);
    state_add_transition(&q1, &q2, (matcher_t *)&matcher_b);

    nfa_t nfa = nfa_init(q0);
    nfa_add(&nfa, q1, false);
    nfa_add(&nfa, q2, true);

    printf("%d\n", nfa_process(&nfa, "ab"));
    printf("\n");

    state_free(&q0);
    state_free(&q1);
    state_free(&q2);

    nfa_free(&nfa);
}

int main()
{
    example1();
    example2();

    return 0;
}
