#include "toml.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t *read_toml(uint8_t *path) { 
    // This shouldn't be null since find config should handle that case
    // Also this NEEDS to be read bytes since windows fucking sucks
    FILE *file = fopen(path, "rb");
    uint8_t *buff = malloc(TOML_MAX_SIZE);
    if (buff == NULL)
        panic("Allocation error");
    size_t bytes_read = fread(buff, sizeof(uint8_t), TOML_MAX_SIZE, file);
    if (fgetc(file) != EOF)
        panic("Toml file was way too long and is prob filled with bullshit");
    buff[bytes_read] = '\0';
    fclose(file);
    return buff;
}