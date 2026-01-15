#pragma once 

#include <stdint.h>
#include <string.h>
#include <ctype.h>

// Returns true if a character is present in a string
#define ANY(chr, str) (strchr((str), (chr)) != NULL)

// Skips white space characters
#define SKIP_WS(p) do { while (isspace(*(p))) ++(p); } while (0)

// Print a error message to stderr then exit the program
// This is only for unrecoverable errors 
void panic(const uint8_t *err);