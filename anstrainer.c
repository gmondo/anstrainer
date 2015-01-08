/*
**	Answer Trainer is a simple portable C program to train user on particular knowledge.
**	Knoledge is describer in anstrainer.h.
**	You can compile the program with a commad like
**		cc -o anstrainer anstrainer.c
**	and execute without parameters.
**
**	Author:	Giovanni Mondo	(giovanni.mondo@yahoo.it)
**	Date:	2015/01/06
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "anstrainer.h"
#define MAX_ANS 16

int irand(int max);
char* make_query();

int main() {
	srand(clock());

/* debug logs
	printf("%s\n", contexts[0].query_answers[0].query);
	printf("%d\n", contexts[0].size);
	printf("%s\n", contexts[1].query_answers[1].query);
	printf("%d\n", sizeof(contexts)/sizeof(contexts[0]));
	printf("%d\n", irand(3));
	make_query();
*/
	char *res=make_query();
	char ans[MAX_ANS];
	scanf("%s", ans);
	if ( 0 == strcmp(res, ans) ) {
		printf("That's correct!\n");	
	} else {
		printf("That's wrong, the right answer is %s", res);
	}
}

char* make_query() {
	printf("This is the question");
	return "123";
}

int irand(int max) {
	return rand() % max;
}
