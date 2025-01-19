#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int lineNumber; 
extern char* keywords[];
extern int fsaMatrix[11][26];
extern FILE *input;
extern char instance[9];

enum tokenIDs {
    IDENT_tk,
    INT_tk,
    OPDEL_tk,
    KW_tk,
    EOF_tk
};

struct token {
    enum tokenIDs tokenID;
    char tkInstance[9];
    int lineNum;
};
