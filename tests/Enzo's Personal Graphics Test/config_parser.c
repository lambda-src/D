#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define DEFAULT_HOME NULL //Just incase $HOME doesn't exist, it won't just die.

int8_t *possible_cfg_names[] = {"/.d.conf", "/d.conf"}; 
int8_t *possible_cfg_paths[3] = {"/usr/lib", ".", DEFAULT_HOME};


int8_t *find_config_file(){
	int8_t *config_path = NULL;
	FILE *file_pointer = NULL;
	for(uint8_t i = 0; i < 4; i++){
		if(possible_cfg_paths[i] == NULL){ //Paths that make use of Enviroment Variables that weren't initialized for whatever reason won't be checked
			continue;
		}
		//Figure out where its going to look.
		config_path = (int8_t *)malloc(strlen(possible_cfg_paths[i]) + strlen(possible_cfg_names[0]));
		strcpy(config_path, possible_cfg_paths[i]);
		strncat(config_path, possible_cfg_names[0], strlen(possible_cfg_names[0]));

		//Look
		printf("Trying: %s\n", config_path);
		file_pointer = fopen(config_path, "rb");
		if(file_pointer != NULL){
			printf("Found: %s !\n", config_path);
			fclose(file_pointer);
			break;
		}
		free(config_path);
	}
	return config_path;
}


int main(){
	possible_paths[3] = getenv("HOME");
	int8_t *config_file = find_config_file();
	return 0;
}
