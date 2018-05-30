#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
typedef unsigned char BYTE;
int main(){
	//Open file to read Plaintext
	FILE *fp = fopen("plaintext", "rb");
	if(fp == NULL){
		fprintf(stderr, "Failed to open plaintext file!\n");
		exit(1);
	}
	//Open file to write encrypted text
	FILE *fp_out = fopen("encrypted", "wb");
	if(fp_out == NULL){
		fprintf(stderr, "Failed to open encrypted file\n");
		exit(1);
	}
	//Get the file size of plaintext
	size_t FileSize = 0;
	fseek(fp, 0, SEEK_END);
	FileSize = ftell(fp);
	rewind(fp);

	//Allocate memory to get plaintext buffer
	unsigned char *buffer = (unsigned char *)malloc(FileSize + 1);
	//Read plaintext to buffer
	fread(buffer, sizeof(BYTE), FileSize, fp);

	//Encrypt file, What is this?	
	size_t i = 0;
	const BYTE encryption_key[4] = {'C','S','E','C'};
	for(i = 0 ; i < FileSize ; i++){
		buffer[i] = buffer[i] ^ encryption_key[i % 4];
	}	
	
	//Save encrypted buffer to file
	fwrite(buffer, sizeof(BYTE), FileSize, fp_out);

	fclose(fp);
	fclose(fp_out);
}
