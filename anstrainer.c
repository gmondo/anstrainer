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
#define MAX_ANS 5

int irand(int max);
void make_query(char *ans);

int main() {
	char right_ans[MAX_ANS];
	char user_ans[MAX_ANS]; 
	int score = 0;

	/* initialize random generator */
	srand(clock());

/* debug logs
	printf("Number of contexts: %d\n", sizeof(contexts)/sizeof(contexts[0]));
	printf("%s\n", contexts[0].query_answers[0].query);
	printf("%d\n", contexts[0].size);
	printf("%s\n", contexts[1].query_answers[1].query);
	printf("%d\n", irand(3));
	make_query();
*/
	printf("Welcome to Answer Trainer!\n");
	printf("Answer with the each digit containing a right responses or - if none is present.\n\n");

	do {
		make_query(right_ans);
		scanf("%s", user_ans);
		if ( 0 == strcmp(right_ans, user_ans) ) {
			score++;
			printf("That's correct!\n");	
		} else {
			score--;
			printf("That's wrong, the right answer is %s\n", right_ans);
		}
		printf("Your score is %d, continue? [Y/n]", score);
		scanf("%s", user_ans);
	} while ( 0 != strcmp("n", user_ans));
} /* main */

int tot_ctxts = sizeof(contexts)/sizeof(contexts[0]);
void make_query(char *ans) {
	int ctx_idx = irand(tot_ctxts);
	int right_idx = irand(contexts[ctx_idx].size);
	int icount, jcount;
	int rnd_idx;
	int res_idx;
	int res_len = 0;
	char responses[MAX_ANS][MAX_RESPONSE_LEN];
	char res[MAX_ANS];

	printf("%s\n", contexts[ctx_idx].query_answers[right_idx].query);
	for (icount = 0; icount < MAX_ANS; icount++) {
		res[icount] = 0;
		rnd_idx = irand(contexts[ctx_idx].size);
		res_idx = irand(contexts[ctx_idx].query_answers[rnd_idx].size);
		sprintf(responses[icount], "%s", contexts[ctx_idx].query_answers[rnd_idx].answers[res_idx]);
/*
*/
printf("%d) %s\n", icount+1, responses[icount]);
		if (rnd_idx == right_idx) {
			res[icount] = 1;
		} else {
			/* check if another question has the same response */
			for (jcount = 0; jcount < contexts[ctx_idx].query_answers[right_idx].size; jcount++) {
				if (0 == strcmp(contexts[ctx_idx].query_answers[right_idx].answers[jcount], contexts[ctx_idx].query_answers[rnd_idx].answers[res_idx])) {
					res[icount] = 1;
					break;
				}
			}		
		}
	}
	/* remove duplicated responses */
	for (icount = 0; icount < MAX_ANS - 1; icount++) {
		for (jcount = icount + 1; jcount < MAX_ANS; jcount++) {
			if (0 == strcmp(responses[icount], responses[jcount])) {
/*
*/
printf("removing %d\n", jcount);
				responses[jcount][0]=0;
				res[jcount] = 0;
			}
		}
	}
	/* print responses and prepare answer */
	icount = 1;
	for (jcount = 0; jcount < MAX_ANS; jcount++) {
		if (responses[jcount][0]) {
			if (res[jcount]) {
				ans[res_len++]='0' + icount;
			}
			printf("%d) %s\n", icount++, responses[jcount]);
		}
	}
	if (0 == res_len) {
		ans[res_len++] = '-';
	}
	ans[res_len] = '\0';
	return;
} /* make_query */

int irand(int max) {
	return rand() % max;
}
