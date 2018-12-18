#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

int main(int argc, char** argv) {
	assert(argc == 3);
	size_t len = strlen(argv[1]);
	char * txt_file_name = malloc(len+1+4); //Add 4 for ".txt"
	strcpy(txt_file_name, argv[1]); //Get the name of the file
	strcat(txt_file_name, ".txt");
	char* fn = argv[1];
	int file_size;
	sscanf(argv[2], "%d", &file_size);
	FILE* f = fopen(fn, "rb");
	FILE* txt_file = fopen(txt_file_name, "w"); //Open as write
	//printf("char a[%d] = {\n", file_size);
	fprintf(txt_file, "char a[%d] = {\n", file_size);
	unsigned long n = 0;
	while(n < file_size) {
		unsigned char c;
		fread(&c, 1, 1, f);
		//printf("0x%.2X,", (int)c);
		fprintf(txt_file, "0x%.2X,", (int)c);
		++n;
		if(n % 10 == 0)
        {
            //printf("\n",n);
            fprintf(txt_file, "\n",n);
		}
	}
	fclose(f);
	//printf("};\n");
	fprintf(txt_file, "};\n");
}
