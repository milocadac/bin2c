#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_N_BLOCKS 8

int main(int argc, char** argv) {
	assert(argc == 4);
	size_t len = strlen(argv[1]);
	char * txt_file_name = malloc(len+1+4); //Add 4 for ".txt"
	char * block_txt_file_name = malloc(sizeof(txt_file_name)+2);
	strcpy(txt_file_name, argv[1]); //Get the name of the file
	char* fn = argv[1];
	int file_size;
	int block_size;
	int current_block_size;
	sscanf(argv[2], "%d", &file_size);
	sscanf(argv[3], "%d", &block_size);
	int n_blocks = file_size/block_size;
	int last_block_size = file_size%block_size;

	if(last_block_size != 0)
        n_blocks++;

	FILE* f = fopen(fn, "rb");
	FILE* txt_file[MAX_N_BLOCKS] = {}; //Array of file pointers for write
	char txt_file_label[2] = {};
    unsigned long n;

	for(int i = 0; i < n_blocks; i++)
    {
        itoa(i, txt_file_label, 10);
        strcpy(block_txt_file_name, txt_file_name); //Get the name of the file
        strcat(block_txt_file_name, txt_file_label); //Label file
        strcat(block_txt_file_name, ".txt"); //and add txt extension

        //printf(block_txt_file_name);

        if((i == n_blocks-1)&&(last_block_size!=0))
            current_block_size = last_block_size; //Last block case
        else
            current_block_size = block_size;

        txt_file[i] = fopen(block_txt_file_name, "w"); //Open as write
        fprintf(txt_file[i], "char a[%d] = {\n", current_block_size);
        n = 0;
        while(n < current_block_size) {
            unsigned char c;
            fread(&c, 1, 1, f);
            //printf("0x%.2X,", (int)c);
            fprintf(txt_file[i], "0x%.2X,", (int)c);
            ++n;
            if(n % 10 == 0)
            {
                //printf("\n",n);
                fprintf(txt_file[i], "\n",n);
            }
        }
        fprintf(txt_file[i], "};\n");
        fclose(txt_file[i]);
	}

	fclose(f);
}
