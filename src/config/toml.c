#include "toml.h"
#include "util.h"
#include "configure.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// This needs to be reworked holy moly
TomlTable *parse_toml(uint8_t *toml_str) {
    TomlTable *tables = calloc(CONFIGURABLE_ITEMS, sizeof(TomlTable));
    uint8_t *toml_ptr = toml_str;
    TomlTable *curr_table = NULL;
    size_t table_count = 0;

    if (tables == NULL) 
        panic("Allocation error");

    while (*toml_ptr) {
        SKIP_WS(toml_ptr);
        
        // If it's the start to a table name then parse the table
        if (*toml_ptr == '[') {
            // Skip past the '['
            toml_ptr++;
            uint8_t table_name[16];
            size_t i = 0;

            // Loop until the end of the name is hit
            while (*toml_ptr != ']') {
                if (i >= 15) panic("The name was too long");
                table_name[i++] = *toml_ptr++;
            } 

            // Skip past the ']'
            toml_ptr++;
            table_name[i] = '\0';

            curr_table = &tables[table_count++];
            // Copy over the bytes read + 1 for the null terminator
            memcpy(curr_table->name, table_name, i + 1);

            curr_table->pairs = calloc(MAX_PAIRS, sizeof(TomlPair));
            if (curr_table->pairs == NULL) 
                panic("Allocation error");
    
            continue;
        }

        // Parse each key value pair 
        if (curr_table && *toml_ptr) {
            TomlPair *pair = curr_table->pairs;
            uint8_t key[16];
            size_t i = 0;

            // Find the next availible pair
            while (pair->name[0] != '\0') pair++;

            // Read the key name
            while (!ANY(*toml_ptr, " =\r\t\n")) {
                if (i >= 15) panic("Key way too long");
                key[i++] = *toml_ptr++;
            }

            key[i] = '\0';
            memcpy(pair->name, key, i + 1);
            // Advance to right before the '='
            SKIP_WS(toml_ptr);

            if (*toml_ptr != '=')
                panic("Expected a '=' character after the key");

            toml_ptr++;
            SKIP_WS(toml_ptr);

            // Parse the actual value 
            if (!strncmp(toml_ptr, "true", 4)) {
                pair->type = Bool;
                pair->val.boolean = true;
                toml_ptr += 4;
            } else if (!strncmp(toml_ptr, "false", 5)) {
                pair->type = Bool;
                pair->val.boolean = false;
                toml_ptr += 5;
            } else if (*toml_ptr == '"') {
                toml_ptr++;
                uint8_t *key_str = malloc(16);
                size_t j = 0;

                if (key_str == NULL) 
                    panic("Allocation error");

                while (*toml_ptr && *toml_ptr != '"')
                    key_str[j++] = *toml_ptr++;

                if (*toml_ptr != '"')
                    panic("String has no edning quote");

                toml_ptr++;
                key_str[j] = '\0';

                pair->type = String;
                pair->val.string = key_str;
            // If its an array of strings
            } else if (*toml_ptr == '[') {
                toml_ptr++;
                SKIP_WS(toml_ptr);

                pair->type = ArrayString;
                pair->val.arr_string = malloc(sizeof(uint8_t *));
                size_t str_count = 0;

                if (pair->val.arr_string == NULL)
                    panic("Allocation error");

                while (*toml_ptr && *toml_ptr != ']') {
                    if (*toml_ptr != '"')
                        panic("Expected a string ");

                    toml_ptr++;
                    uint8_t *str_buff = malloc(16);
                    size_t j = 0;

                    if (str_buff == NULL)
                        panic("Allocation error");

                    while (*toml_ptr && *toml_ptr != '"')
                        str_buff[j++] = *toml_ptr++;

                    if (*toml_ptr != '"')
                        panic("String has no ending quote");

                    toml_ptr++;
                    str_buff[j] = '\0';

                    pair->val.arr_string[str_count++] = str_buff;

                    SKIP_WS(toml_ptr);
                    if (*toml_ptr == ',') {
                        toml_ptr++;
                        SKIP_WS(toml_ptr);
                    }
                }

                if (*toml_ptr != ']')
                    panic("Array has no closing bracket");

                toml_ptr++;
            } else panic("Unknown value type");
            continue;
        }
        toml_ptr++;
    }
    return tables;
}

void free_toml(TomlTable *toml_tables) {
    // TODO
}