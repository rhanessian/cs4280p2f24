#include "scanner.h"
#include "token.h"
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int lineNumber = 1;
char instance[15] = "";
int c = 0;
int value = 0;
int newLineNum = 1;
int statStringNum = 100;
int relationalNum = 100;

char* relationalStrings[] = {".le.", ".ge.", ".lt.", ".gt.", "**", "~"};
char* statStrings[] = {"read", "print", "start", "iff", "iterate", "set"};

int fsaMatrix[11][26] = 
 		{{1,1,1,1,1,2,1003,3,1003,1003,1003,1003,1003,10,1003,1003,1003,1003,1003,1003,1003,1003,1003,-4,0,-1},
  		{1,1,1,1,1,1,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1001,1,1001,-1},
  		{1002,1002,1002,1002,1002,2,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,1002,-4,1002,-1},
  		{-5,4,5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,7,6,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,9,8,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,-5,-5,-5,-5,1003,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,-5,-5,-5,-5,1003,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,-5,-5,-5,-5,1003,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-5,-5,-5,-5,-5,-5,-5,1003,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-5,-1},
  		{-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,1003,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-3,-1}};
  
char* keywords[] = {"start",
					"stop",
					"iterate",
					"var",
					"exit",
					"read",
					"print",
					"iff",
					"then",
					"set",
					"func",
					"program"};

int filter() {
	
// Get next char in input, counting lines and checking for eof
	
	c = fgetc(input);
    
// Ignore comments	

	if (c == 64) {
		c = fgetc(input);
		if (c == 64) {
			do {
				c = fgetc(input);
				if (c == 10)
					lineNumber++;
			} while (c != 64);
		} else {
			perror("ERROR: Incomplete comment creation.\n");
			exit(1);
		}
		c = fgetc(input);
	}
	
	if (c == EOF) {
        return 99;
    }
    
    if (c == 10) {
    	lineNumber++;
    	newLineNum = lineNumber;
    }
	
// Get column number of char in FSA alphabet matrix (using ASCII values)
	
	int columnNum = 0;
	switch(c) {
		case 65 ... 90:
			columnNum = 0;
			break;
		case 97 ... 100:
			columnNum = 0;
			break;
		case 101:
			columnNum = 4;
			break;
		case 102:
			columnNum = 0;
			break;
		case 103:
			columnNum = 2;
			break;
		case 104 ... 107:
			columnNum = 0;
			break;
		case 108:
			columnNum = 1;
			break;
		case 109 ... 115:
			columnNum = 0;
			break;
		case 116:
			columnNum = 3;
			break;
		case 117 ... 122:
			columnNum = 0;
			break;
		case 48 ... 57:
			columnNum = 5;
			break;
		case 61:
			columnNum = 6;
			break;
		case 46:
			columnNum = 7;
			break;
		case 126:
			columnNum = 8;
			break;
		case 59:
			columnNum = 9;
			break;
		case 58:
			columnNum = 10;
			break;
		case 43:
			columnNum = 11;
			break;
		case 45:
			columnNum = 12;
			break;
		case 42:
			columnNum = 13;
			break;
		case 47:
			columnNum = 14;
			break;
		case 37:
			columnNum = 15;
			break;
		case 40:
			columnNum = 16;
			break;
		case 41:
			columnNum = 17;
			break;
		case 44:
			columnNum = 18;
			break;
		case 123:
			columnNum = 19;
			break;
		case 125:
			columnNum = 20;
			break;
		case 91:
			columnNum = 21;
			break;
		case 93:
			columnNum = 22;
			break;
		case 95:
			columnNum = 23;
			break;
		case 32:
			columnNum = 24;
			break;
		case 9 ... 13:
			columnNum = 24;
			break;
		default:
			columnNum = 25;
			break;
	}
	return columnNum;
	
}

struct token scanner() {
	if (input == NULL) {
		perror("ERROR: File did not open.\n");
		exit(1);
	}
	instance[0] = '\0';
	
	int c1 = 0;
	int c2 = 0;
	char ch1;
	struct token tk;
	int row = 0;
	int col = 0;
	bool finalState = false;
	enum tokenIDs tkClass = IDENT_tk;
	int len = 0;
	newLineNum = lineNumber;

	col = filter();
	c1 = c;
	ch1 = (char) c1;
	
	if (col == 99) {
		tkClass = EOF_tk;
		tk.tokenID = tkClass;
		strcpy(tk.tkInstance, instance);
		tk.lineNum = lineNumber;
		return tk;
	}
	
	value = fsaMatrix[row][col];
	switch (value) {
		case 1003:
			len = strlen(instance);
			if (!isspace(ch1)) {
				instance[len] = ch1;
				instance[len + 1] = '\0';
			} 
			tkClass = OPDEL_tk;
			tk.tokenID = tkClass;
			strcpy(tk.tkInstance, instance);
			tk.lineNum = lineNumber;
			int k;
			for(k = 0; k < 6; k++) {
    			if(strcmp(relationalStrings[k], instance) == 0) {
    				relationalNum = k;
    				break;
    			}
    		}
			return tk;
		case 0 ... 10:
			row = value;
			break;
		case -1:
			perror("ERROR: Input not recognized.\n");
			exit(1);
			break;
		case -3:
			perror("ERROR: * not followed by *, thus not recognized.\n");
			exit(1);
			break;
		case -4:
			perror("ERROR: _ used to start a token.\n");
			exit(1);
			break;
		case -5:
			perror("ERROR: Incomplete lesser/greater than operator.\n");
			exit(1);
			break;
		default:
			printf("Row: %d, Col: %d \n", row, col);
    		perror("ERROR: Unrecognized value.\n");
    		exit(1);
    		break;
    }
	
	while (!finalState) {
		col = filter();
		c2 = c;
		if (col == 99)
			break;
		value = fsaMatrix[row][col];
		switch (value) {
			case -1:
				perror("ERROR: Input not recognized.\n");
				exit(1);
				break;
			case -3:
				perror("ERROR: * not followed by *, thus not recognized.\n");
				exit(1);
				break;
			case -4:
				perror("ERROR: _ used to start a token.\n");
				exit(1);
				break;
			case -5:
				perror("ERROR: Incomplete lesser/greater than operator.\n");
				exit(1);
				break;
			case 1001:
				tkClass = IDENT_tk;
    			finalState = true;
    			break;
    		case 1002:
    			tkClass = INT_tk;
    			finalState = true;
    			break;
    		case 1003:
    			tkClass = OPDEL_tk;
    			finalState = true;
    			break;
    		case 0 ... 10:
    			row = value;
    			break;
    		default:
    			printf("Row: %d, Col: %d \n", row, col);
    			perror("ERROR: Unrecognized value.\n");
    			exit(1);
    			break;
    	}
    	
    	len = strlen(instance);
		if (!isspace(ch1)) {
			instance[len] = ch1;
			instance[len + 1] = '\0';
		} 
		
		c1 = c2;
		ch1 = (char) c1;
	}
	
	if (c == 10 && (value == 1001 || value == 1002) && lineNumber > 1) {
    	newLineNum = lineNumber - 1;	
    }
	
	if (value == 1003) {
		len = strlen(instance);
		if (!isspace(ch1)) {
			instance[len] = ch1;
			instance[len + 1] = '\0';
		} 
	}
		
	if (!isspace(ch1) && value != 1003) {
		ungetc(c, input);
	} 
	
	int i, j, k;
	for(i = 0; i < 12; i++) {
    	if(strcmp(keywords[i], instance) == 0) {
            value = 1004;
            tkClass = KW_tk;
            break;
        }
    }
    
    if (tkClass == KW_tk) {
    	for(j = 0; j < 6; j++) {
    		if(strcmp(statStrings[j], instance) == 0) {
            	statStringNum = j;
            	break;
            }
    	}
    }
    
    for(k = 0; k < 6; k++) {
    	if(strcmp(relationalStrings[k], instance) == 0) {
    		relationalNum = k;
    		break;
    	}
    }
	
	if (col == 99) {
		tkClass = EOF_tk;
	}
	
	tk.tokenID = tkClass;
	strcpy(tk.tkInstance, instance);
	if (value != 1003) {
		tk.lineNum = newLineNum;
	} else {
		tk.lineNum = lineNumber;
	}
	return tk;
}