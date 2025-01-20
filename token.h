#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern int lineNumber; 
extern char* keywords[];
extern int fsaMatrix[11][26];
extern FILE *input;
extern char instance[15];
extern int statStringNum;
extern int relationalNum;

enum tokenIDs {
    IDENT_tk,
    INT_tk,
    OPDEL_tk,
    KW_tk,
    EOF_tk
};

struct token {
    enum tokenIDs tokenID;
    char tkInstance[15];
    int lineNum;
};

extern char tokenClass[19];

struct node {
    char lab[15];  
    struct token tkArray[15];
    struct node* child1;
    struct node* child2;
    struct node* child3;
    struct node* child4;
};