#include "matcher.h"

bool matcher_matches(matcher_t *matcher, const char c)
{
    switch (MATCHER_TYPE(matcher))
    {
    case MATCHER_CHAR:
        return AS_MATCHER_CHAR(matcher)->c == c;

    case MATCHER_EPSILON:
        return true;
    
    default:
        NOT_IMPLEMENTED;
    }
}

void matcher_print(matcher_t *matcher)
{
    switch (MATCHER_TYPE(matcher))
    {
    case MATCHER_CHAR:
    {
        printf("%c\n", AS_MATCHER_CHAR(matcher)->c);
    } break;

    case MATCHER_EPSILON:
    {
        printf("ε\n");
    } break;
    
    default:
        printf("undefined-matcher");
    }
}

matcher_t matcher_new(matcher_type_t type)
{
    return (matcher_t)
    {
        .type = type
    };
}

matcher_char_t matcher_char_new(const char c)
{
    return (matcher_char_t)
    {
        .matcher = matcher_new(MATCHER_CHAR),
        .c = c
    };
}

matcher_t matcher_epsilon_new()
{
    return matcher_new(MATCHER_EPSILON);
}
