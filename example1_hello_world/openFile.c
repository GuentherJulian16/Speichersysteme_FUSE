#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE *fp;
	fp=fopen("/tmp/hello/hello", "r");
	
	if(fp == NULL) {
		printf("Datei konnte nicht geöffnet werden!");
	} else {
		fclose(fp);
	}
	
	return 0;
}
