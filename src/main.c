#include <stdio.h>

int main(int argc, char *argv[]){
	if(argc <= 1){
		printf("Hello World!");
	}else{
		printf(argv[1]);
	}
	return 0;
}
