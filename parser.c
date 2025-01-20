#include "token.h"
#include "parser.h"
#include "scanner.h"

struct token scannertoken;
char tokenClass[19] = "";
char* tokenNames[] = {"Identifier", "Integer", "Operator/Delimiter", "Keyword", "End of File"};

void parser() {
	printf("IN PARSER()\n");
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	program();
	if (scannertoken.tokenID == EOF_tk) {
		return;
	} else {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: EOF_tk expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
}

void program() {
	printf("IN PROGRAM()\n");
	if (strcmp(scannertoken.tkInstance, "program") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'program' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	vars();
	block();
	return;
}

void vars() {
	printf("IN VARS()\n");
	if (strcmp(scannertoken.tkInstance, "var") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		varList();
		return;
	} else
		return;
}

void varList() {
	printf("IN VARLIST()\n");
	if (scannertoken.tokenID != IDENT_tk) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ",") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ',' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != INT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: integer expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ";") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return;
	} else {
		varList();
	}
	return;
}

void stats() {
	printf("IN STATS()\n");
	stat();
	mStat();
	return;
}

void mStat() {
	printf("IN MSTAT()\n");
	printf("stat string num = %d\n", statStringNum);
	switch (statStringNum) {
		case 0:
			stat();
			mStat();
			return;
		case 1:
			stat();
			mStat();
			return;
		case 2:
			stat();
			mStat();
			return;
		case 3:
			stat();
			mStat();
			return;
		case 4:
			stat();
			mStat();
			return;
		case 5:
			stat();
			mStat();
			return;
		default:
			return;
	}
}

void stat() {
	printf("IN STAT()\n");
	printf("stat string num = %d\n", statStringNum);
	if (statStringNum != 100) {
		switch (statStringNum) {
			case 0:
				read();
				return;
			case 1:
				print();
				return;
			case 2:
				block();
				return;
			case 3:
				cond();
				return;
			case 4:
				iter();
				return;
			case 5:
				assign();
				return;
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

void block() {
	printf("IN BLOCK()\n");
	if (strcmp(scannertoken.tkInstance, "start") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'start' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	vars();
	stats();
	if (strcmp(scannertoken.tkInstance, "stop") != 0) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'stop' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	} 
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return;
}

void read() {
	printf("IN READ()\n");
	if (strcmp(scannertoken.tkInstance, "read") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'read' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != IDENT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return;
}

void print() {
	printf("IN PRINT()\n");
	if (strcmp(scannertoken.tkInstance, "print") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'print' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	expr();
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return;
}

void cond() {
	printf("IN COND()\n");
	if (strcmp(scannertoken.tkInstance, "iff") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'iff' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, "[") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: '[' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	expr();
	relational();
	expr();
	if (strcmp(scannertoken.tkInstance, "]") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ']' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	stat();
	return;
}

void iter() {
	printf("IN ITER()\n");
	if (strcmp(scannertoken.tkInstance, "iterate") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'iterate' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (strcmp(scannertoken.tkInstance, "[") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: '[' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	expr();
	relational();
	expr();
	if (strcmp(scannertoken.tkInstance, "]") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ']' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	stat();
	return;
}

void assign() {
	printf("IN ASSIGN()\n");
	if (strcmp(scannertoken.tkInstance, "set") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: 'set' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	if (scannertoken.tokenID != IDENT_tk){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	expr();
	if (strcmp(scannertoken.tkInstance, ";") != 0){
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: ';' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	}
	statStringNum = 100;
	scannertoken = scanner();
	strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
	printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
	return;
}

void relational() {
	printf("IN RELATIONAL()\n");
	printf("relational num = %d\n", relationalNum);
	switch (relationalNum) {
		case 0 ... 5:
			scannertoken = scanner();
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
			return;
		default:
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			fprintf(stderr, "ERROR: relational operator expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
			exit(1);
	}
}

void expr() {
	printf("IN EXPR()\n");
	M();
	if (strcmp(scannertoken.tkInstance, "+") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		expr();
		return;
	} else if (strcmp(scannertoken.tkInstance, "-") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		expr();
		return;
	} else
		return;
}

void M() {
	printf("IN M()\n");
	N();
	if (strcmp(scannertoken.tkInstance, "%") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		M();
		return;
	} else
		return;
}

void N() {
	printf("IN N()\n");
	if (strcmp(scannertoken.tkInstance, "-") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		N();
		return;
	} else {
		R();
		if (strcmp(scannertoken.tkInstance, "/") == 0) {
			scannertoken = scanner();
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
			N();
			return;
		} else
			return;
	}
}

void R() {
	printf("IN R()\n");
	if (strcmp(scannertoken.tkInstance, "(") == 0) {
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		expr();
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		if (strcmp(scannertoken.tkInstance, ")") != 0) {
			strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
			fprintf(stderr, "ERROR: ')' expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
			exit(1);
		}
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return;
	} else if (scannertoken.tokenID != IDENT_tk && scannertoken.tokenID != INT_tk) {
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		fprintf(stderr, "ERROR: identifier or integer expected but received '%s' of class '%s'\n", scannertoken.tkInstance, tokenClass);
		exit(1);
	} else
		scannertoken = scanner();
		strcpy(tokenClass, tokenNames[scannertoken.tokenID]);
		printf("{%s, %s, %d}\n", tokenClass, scannertoken.tkInstance, scannertoken.lineNum);
		return;
}


