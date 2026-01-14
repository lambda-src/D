#pragma once 

#include "toml.h"
#include <stdint.h>

// Some configurable stuff you can do in ncurses
// This will all need to be parsed from a toml file then ran in
// editor_start() and maybe editor_exit()
typedef enum {
    Invisible,
    Normal,
    Strong
} CursorAppearnce;

typedef enum {
    Black,
    Red, 
    Green, 
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Default // Same with Background color comment
} TextColor;

typedef enum {
    Underline,
    Reverse,
    Blink, 
    Dim,
    Bright, // I think this attribute may be named bold 
    Blank, // I think this is called invisible 
    Invisible, // Not really too sure why u would want this one 
} TextStyle;

typedef enum {
    Black,
    Red, 
    Green, 
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White,
    Default // Default is to use the users terminal default settings 
            // This is needed if you want a transparent background
} BackgroundColor;

typedef enum {
    SaveOnExit, 
    // idk if we actually wanna do these but they do seem fun
    // Also we should find some more fun stuff to add! 
    DisplayAsHex, 
    DisplayAsBytes
} EditorSettings;

typedef struct {
    CursorAppearnce cursor_appearnce;
    TextColor text_color;
    TextStyle *text_style; 
    BackgroundColor background_color;
    // idk if this should be a bunch of flags or an array of settings lets just change it later if need3
    EditorSettings *editor_settings;
} Config;

void grab_envs(); // Grabs important Enviroment Variables

int8_t *find_config_file(); // Finds where the config file is

Config *get_config(TomlTable *toml_tables);