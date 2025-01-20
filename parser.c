#include "token.h"
#include "parser.h"
#include "scanner.h"

struct token scannertoken;
char tokenClass[19] = "";
char* tokenNames[] = {"Identifier", "Integer", "Operator/Delimiter", "Keyword", "End of File"};

struct node* parser() {
	struct node* root;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	root = program();
	if (scannertoken.tokenID == EOF_tk) {
		return root;
	} else {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: EOF_tk expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
}

struct node* program() {
	struct node* p = getNode("Program");
	if (strcmp(scannertoken.tkInstance, "program") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'program' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = vars();
	p->child2 = block();
	return p;
}

struct node* vars() {
	struct node* p = getNode("Vars");
	if (strcmp(scannertoken.tkInstance, "var") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child1 = varList();
		return p;
	} else
		return NULL;
}

struct node* varList() {
	struct node* p = getNode("VarList");
	if (scannertoken.tokenID != IDENT_tk) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ",") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ',' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != INT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: integer expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[2] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ";") == 0) {
		p->tkArray[3] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return p;
	} else {
		p->child1 = varList();
	}
	return p;
}

struct node* stats() {
	struct node* p = getNode("Stats");
	p->child1 = stat();
	p->child2 = mStat();
	return p;
}

struct node* mStat() {
	struct node* p = getNode("MStat");
	switch (statStringNum) {
		case 0 ... 5:
			p->child1 = stat();
			p->child2 = mStat();
			return p;
		default:
			return NULL;
	}
}

struct node* stat() {
	struct node* p = getNode("Stat");
	if (statStringNum != 100) {
		switch (statStringNum) {
			case 0:
				p->child1 = read();
				return p;
			case 1:
				p->child1 = print();
				return p;
			case 2:
				p->child1 = block();
				return p;
			case 3:
				p->child1 = cond();
				return p;
			case 4:
				p->child1 = iter();
				return p;
			case 5:
				p->child1 = assign();
				return p;
			default:
				strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
				fprintf(stderr, "ERROR: stat first set tokens expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
				exit(1);
		}
	} else {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: stat first set tokens expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
}

struct node* block() {
	struct node* p = getNode("Block");
	if (strcmp(scannertoken.tkInstance, "start") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'start' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = vars();
	p->child2 = stats();
	if (strcmp(scannertoken.tkInstance, "stop") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'stop' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	} 
	p->tkArray[1] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return p;
}

struct node* read() {
	struct node* p = getNode("Read");
	if (strcmp(scannertoken.tkInstance, "read") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'read' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != IDENT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[2] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return p;
}

struct node* print() {
	struct node* p = getNode("Print");
	if (strcmp(scannertoken.tkInstance, "print") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'print' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = expr();
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return p;
}

struct node* cond() {
	struct node* p = getNode("Cond");
	if (strcmp(scannertoken.tkInstance, "iff") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'iff' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, "[") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: '[' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = expr();
	p->child2 = relational();
	p->child3 = expr();
	if (strcmp(scannertoken.tkInstance, "]") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ']' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[2] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child4 = stat();
	return p;
}

struct node* iter() {
	struct node* p = getNode("Iter");
	if (strcmp(scannertoken.tkInstance, "iterate") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'iterate' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, "[") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: '[' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = expr();
	p->child2 = relational();
	p->child3 = expr();
	if (strcmp(scannertoken.tkInstance, "]") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ']' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[2] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child4 = stat();
	return p;
}

struct node* assign() {
	struct node* p = getNode("Assign");
	if (strcmp(scannertoken.tkInstance, "set") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'set' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[0] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != IDENT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[1] = scannertoken;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	p->child1 = expr();
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	p->tkArray[2] = scannertoken;
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return p;
}

struct node* relational() {
	struct node* p = getNode("Relational");
	switch (relationalNum) {
		case 0 ... 5:
			p->tkArray[0] = scannertoken;
			scannertoken = scanner();
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
			return p;
		default:
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			fprintf(stderr, "ERROR: relational operator expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
			exit(1);
	}
}

struct node* expr() {
	struct node* p = getNode("Expr");
	p->child1 = M();
	if (strcmp(scannertoken.tkInstance, "+") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child2 = expr();
		return p;
	} else if (strcmp(scannertoken.tkInstance, "-") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child2 = expr();
		return p;
	} else
		return p;
}

struct node* M() {
	struct node* p = getNode("M");
	p->child1 = N();
	if (strcmp(scannertoken.tkInstance, "%") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child2 = M();
		return p;
	} else
		return p;
}

struct node* N() {
	struct node* p = getNode("N");
	if (strcmp(scannertoken.tkInstance, "-") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child1 = N();
		return p;
	} else {
		p->child1 = R();
		if (strcmp(scannertoken.tkInstance, "/") == 0) {
			p->tkArray[0] = scannertoken;
			scannertoken = scanner();
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
			p->child2 = N();
			return p;
		} else
			return p;
	}
}

struct node* R() {
	struct node* p = getNode("R");
	if (strcmp(scannertoken.tkInstance, "(") == 0) {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		p->child1 = expr();
		p->tkArray[1] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		if (strcmp(scannertoken.tkInstance, ")") != 0) {
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			fprintf(stderr, "ERROR: ')' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
			exit(1);
		}
		p->tkArray[2] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return p;
	} else if (scannertoken.tokenID != IDENT_tk && scannertoken.tokenID != INT_tk) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier or integer expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	} else {
		p->tkArray[0] = scannertoken;
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return p;
	}
}

struct node* getNode(char* label) {
	struct node* currentNode = malloc(500);
	strcpy(currentNode->lab, label);
	return currentNode;
}


