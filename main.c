//Rebecca Hanessian
//CS 4280
//P1

#include "testScanner.h"
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

FILE *input;

int main (int argc, const char *argv[]){
	int c;
	input = tmpfile();
	
	//Parse arguments and take input; write input to temp file
	if (argc > 2) 
    {
        printf( "usage: %s filename", argv[0] );
        return 1;
    }
    else if (argc == 1){
    	printf("Begin input and end with ctrl-D:\n");
    	input = fopen("temptext.txt", "w+");
    	if(input == NULL) {
    		printf("Error writing to temp file.\n");
    		fclose(input);
    		return 1;
    	}
    	
    	while ((c = fgetc(stdin)) != EOF)
    	{
        	fputc(c, input);
    	}	
    }
    else 
    {
    	char tempstring[128];
		sprintf(tempstring, "%s.4280fs24", argv[1]);
        FILE *file = fopen(tempstring, "r");

        if (file == NULL)
        {
            printf( "File could not be opened.\n" );
            fclose(input);
            return 1;
        }
        
        input = fopen("temptext.txt", "w+");
    	if(input == NULL) {
    		printf("Error writing to temp file.\n");
    		fclose(input);
    		return 1;
    	}
    	
    	while ((c = fgetc(file)) != EOF)
    	{
        	fputc(c, input);
    	}
    }
    
    rewind(input);
    testScanner();
    
    fclose(input);
	
	return 0;
}