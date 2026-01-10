#pragma once 

#include <stdint.h>

// Print a error message to stderr then exit the program
// This is only for unrecoverable errors 
void panic(const uint8_t *err);