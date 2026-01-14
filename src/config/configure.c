/* 			--------------------
 *                          CONFIGURE.C
 * 			--------------------
 * This files's goal in life is to setup all the configurations.
 * Handles finding the config file, and setting all the variables
 * after reading it.
 *
 * Created 1/8/26 
 * */
#include "configure.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define PLACEHOLDER_HOME_DIR NULL 
#define OUT_OF_RAM_ERROR NULL //Probably will be removed at some point idk.

int8_t *possible_cfg_names[] = {"/.d.conf", "/d.conf"}; 
int8_t *possible_cfg_paths[3] = {PLACEHOLDER_HOME_DIR, ".", "/usr/lib"};


//Gets the important Enviroment variables. May be split off into its own C file later down the road
void grab_envs(){
	possible_cfg_paths[3] = getenv("HOME");
       return;	
}

//If a config file isn't pointed to in the command prompt, than this function will run to find one. If this fails than settings will just be defaults.
int8_t *find_config_file(){ //Returns path to config file
	int8_t *config_path = NULL;
	FILE *file_pointer = NULL;
	for(uint8_t i = 0; i < 4; i++){
		if(possible_cfg_paths[i] == NULL){ //Paths that make use of Enviroment Variables that weren't initialized for whatever reason won't be checked
			continue;
		}
		//Figure out where its going to check.
		config_path = (int8_t *)malloc(strlen(possible_cfg_paths[i]) + strlen(possible_cfg_names[0]));
		if(config_path == NULL){ //Holy shit
			return OUT_OF_RAM_ERROR;
		}
		strcpy(config_path, possible_cfg_paths[i]);
		strncat(config_path, possible_cfg_names[0], strlen(possible_cfg_names[0]));

		//Check it!
		//printf("Trying: %s\n", config_path);
		file_pointer = fopen(config_path, "rb");
		if(file_pointer != NULL){
			//printf("Found: %s !\n", config_path);
			fclose(file_pointer);
			break;
		}
		free(config_path);
		config_path = NULL;
	}
	return config_path;
}

Config *get_config(TomlTable *toml_tables) {
	Config *config = malloc(sizeof(Config));
	size_t table_count = 0;
	size_t i = 0;

	if (config == NULL)
		panic("Allocation error");

	// Get the number of tables 
	while (toml_tables[i].name[0] != '\0') table_count++;

	for (size_t i = 0; i < table_count; i++) {
		if (strncmp(toml_tables[table_count].name, "cursor", 7)) {
			// Parse cursor table 
		} else if (strncmp(toml_tables[table_count].name, "text", 5)) {
			// Parse text table
		} else if (strncmp(toml_tables[table_count].name, "editor", 7)) {
			// Parse the editor table 
		}
	}

	free_toml(toml_tables);
	return (Config *)NULL;
}
