#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE *fp;
	fp=fopen("/tmp/hello/hello", "r");
	
	if(fp == NULL) {
		printf("Datei konnte nicht geöffnet werden!");
	} else {
		int c;
		while((c = getc(fp)) != EOF)
			putchar(c);
		fclose(fp);
	}
	
	return 0;
}
