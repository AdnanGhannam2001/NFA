#ifndef RE_COMMON_H
#define RE_COMMON_H

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define NOT_IMPLEMENTED assert(0 && "Not Implemented")
#define UNREACHABLE     assert(0 && "Unreachable")
#define UNUSED          __attribute__((unused))

#endif // RE_COMMON_H
