#include <iostream>
#include <cstdio>
#include <arpa/inet.h>
#include "crc32.h"


int main(int argc, const char * argv[]) {
    
    if (argc != 5){
        printf("Usage: pngtext [filepath] [chunk name] [keyword] [payload] \n");
        printf("The output file is named modified.png\n");
        printf("You probably want to call the program like this:\n");
        printf("      pngtext /samplepath/sample.png tEXt sample \"some random text\" \n ");
        
    }
    else{
        char * filepath = (char *) argv[1];
        char * chunk = (char *) argv[2];
        char * keyword = (char *) argv[3];
        char * payload = (char *) argv[4];
        
        FILE *f = fopen(filepath, "rb");
        fseek(f, 0, SEEK_END);
        long fsize = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        long buffersize = fsize + 4 + strlen(chunk) + strlen(keyword) + 1 + strlen(payload) + 4;
        uint8_t *string = (uint8_t *) malloc(buffersize);
        fread(string, fsize, 1, f);
        fclose(f);
        
        int IENDindex = 0;
        for (int i = 0; i<fsize-4; i++){
            if ((string[i]==0x49)&&(string[i+1]==0x45)&&(string[i+2]==0x4E)&&(string[i+3]==0x44)){
                IENDindex = i;
                printf("IEND chunk found after %d bytes\n",i);
                break;
            }
        }
        
        for (int i=1; i<13; i++){
            string[buffersize-i] = string[IENDindex + 8 - i];
        }
        
        int * Sizep = (int *) (string + IENDindex - 4);
        *Sizep = htonl(strlen(payload) + strlen(keyword) + 1);
        
        char * chunknamep = (char *) (string + IENDindex);
        strncpy(chunknamep, chunk, strlen(chunk));
        
        char * keywordp = (char *) (string + IENDindex + strlen(chunk));
        strncpy(keywordp, keyword, strlen(keyword));
        
        string[IENDindex + strlen(chunk) + strlen(keyword)] = 0;
        
        char * textp = (char *) (string + IENDindex + strlen(chunk) + strlen(keyword) + 1);
        strncpy(textp, payload, strlen(payload));
        
        int * crcp = (int *) (string + IENDindex + strlen(chunk) + strlen(keyword) + 1 + strlen(payload));
        uint8_t * buffer = (uint8_t*)(string + IENDindex);
        *crcp = htonl(crc32(0,buffer,(strlen(chunk) + strlen(keyword) + 1 + strlen(payload) )));
        
        FILE * output;
        output = fopen ("modified.png", "wb");
        fwrite (string , sizeof(char), buffersize, output);
        fclose (output);

    }
    return 0;
}
