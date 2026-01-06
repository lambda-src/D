#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int8_t *possible_config_paths[] = {".d.conf", "d.conf"}; // "~/.d.conf", "~/d.conf"};


int main(){
	int8_t *config_path = NULL;
	FILE *d_conf_file;
	for(uint8_t i = 0; i < 2; i++){
		printf("Checking: %s\n", possible_config_paths[i]);
		d_conf_file = fopen(possible_config_paths[i], "rb");
		if(d_conf_file == NULL){
			printf("Couldn't find %s\n", possible_config_paths[i]);
			continue;
		}else{
			config_path = possible_config_paths[i];
			break;
		}
	}

	if(config_path == NULL){
		printf("Error! Couldn't find any config files!\n");
		return 1;
	}else{
		printf("Found %s!\n", config_path);
	}
	return 0;
}
