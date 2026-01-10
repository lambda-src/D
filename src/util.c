#include "util.h"
#include <stdio.h>
#include <stdlib.h>

void panic(const uint8_t *err) {
    fprintf(stderr, "%s\n", err);
    exit(EXIT_FAILURE);
}