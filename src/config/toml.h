#pragma once 

/*
For now the only toml we need to support is string, arrays, and bools, so for instance this could be a config file:
D.toml

[cursor]
appearnce = "strong" 
efjeijfeijf = {} "meow" // This line shoud error 

[text]
foreground = "white"
background = "black"
style = ["underline", "bright", "blink"]

[editor]
save_on_exit = true
display_as_hex = true 
*/

#include <stdint.h>
#include <stdbool.h>

// With how small the toml file is just allocate this much and if it gets filled then the file is filled with gibberish
#define TOML_MAX_SIZE 1024

// This is the most key value pairs that a table can currently have 
#define MAX_PAIRS 3

// This is the number of configurable things that we got 
#define CONFIGURABLE_TABLES 3

typedef enum {
    Bool,
    String,
    ArrayString
} TomlType;

typedef union {
    // Case of: val = true
    bool boolean;
    // Case of: val = "meow"
    uint8_t *string;
    // Case of: val = ["underline", "bright", "blink"]
    uint8_t **arr_string;
} TomlValue;

typedef struct {
    uint8_t name[16];
    TomlValue val;
    TomlType type;
} TomlPair;

typedef struct {
    uint8_t name[16];
    TomlPair *pairs; 
} TomlTable;

// Read the entire toml file into a buffer which should be fine with how small it is
uint8_t *read_toml(uint8_t *path);

// Parse the toml into tables
TomlTable *parse_toml(uint8_t *toml_str);

// Read the toml str and advance the toml ptr
uint8_t *read_toml_str(uint8_t *toml_str);

// Frees all the allocated memory from parse toml
void free_toml(TomlTable *toml_tables);