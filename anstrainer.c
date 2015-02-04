/*
**	Answer Trainer is a simple portable C program to train user on particular knowledge.
**	Knowledge is described in anstrainer.h.
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

int irand(int max);
char* trim(char *);

int main(int argc, char *argv[]) {
	char right_ans[MAX_ANS];
	char user_ans[MAX_ANS]; 
	int score = 0;
	int ctxts_num = 0;
	t_ctxt *contexts = NULL;
	char *fin;

	if (argc < 2) {
		fin = DEF_FIN;
	} else {
		fin = argv[1];
	}

	ctxts_num = load(fin, &contexts);
	if ( ctxts_num < 1 ) {
		fprintf(stdout, "Invalid file %s\n", fin);
		return 1;
	}

	/* initialize random generator */
	srand(clock());

	fprintf(stdout, "Welcome to Answer Trainer!\n");
	fprintf(stdout, "Answer with each digit containing a right responses or - if none is present.\n\n");

	do {
		make_query(contexts, ctxts_num, right_ans);
		scanf("%s", user_ans);
		if ( 0 == strcmp(right_ans, user_ans) ) {
			score++;
			fprintf(stdout, "That's correct!\n");	
		} else {
			score--;
			fprintf(stdout, "That's wrong, the right answer is %s\n", right_ans);
		}
		fprintf(stdout, "Your score is %d, continue? [Y/n]", score);
		scanf("%s", user_ans);
	} while ( 0 != strcmp("n", user_ans));
} /* main */

void make_query(t_ctxt *contexts, int ctxts_num, char *ans) {
	int ctx_idx = irand(ctxts_num);
	int icount, jcount;
	int rnd_idx;
	int res_len = 0;
	char responses[MAX_ANS][MAX_STR];
	char res[MAX_ANS];
	t_ctxt	*cur_ctxt = contexts;
	t_query	*cur_query, *right_query;
	t_answer	*cur_ans;
	
	for (icount = 0; icount < ctx_idx; icount++) {
		cur_ctxt = cur_ctxt->next;
	}
	for (icount = -1; icount < MAX_ANS; icount++) {
		cur_query = cur_ctxt->queries;
		rnd_idx = irand(cur_ctxt->num_queries);
		for (jcount = 0; jcount < rnd_idx; jcount++) {
			cur_query = cur_query->next;
		}
		if (-1 == icount) {
			right_query = cur_query;
			fprintf(stdout, "%s\n", right_query->text);
			continue;
		}
		res[icount] = 0;
		rnd_idx = irand(cur_query->num_answers);
		cur_ans = cur_query->answers;
		for (jcount = 0; jcount < rnd_idx; jcount++) {
			cur_ans = cur_ans->next;	
		}
		sprintf(responses[icount], "%s", cur_ans->text);
/*
fprintf(stderr, "%d) %s<\n", icount+1, responses[icount]);
*/
		if (cur_query == right_query) {
			res[icount] = 1;
		} else {
			/* check if another question has the same response */
			cur_ans = right_query->answers;
			while ( NULL != cur_ans) {
				if (0 == strcmp(cur_ans->text, responses[icount])) {
					res[icount] = 1;
					break;
				}
				cur_ans = cur_ans->next;
			}
		}
	}
	/* remove duplicated responses */
	for (icount = 0; icount < MAX_ANS - 1; icount++) {
		for (jcount = icount + 1; jcount < MAX_ANS; jcount++) {
			if (0 == strcmp(responses[icount], responses[jcount])) {
/*
fprintf(stderr, "removing %d\n", jcount);
*/
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
			fprintf(stdout, "%d) %s\n", icount++, responses[jcount]);
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

char* trim(char *buf) {
	char *res = buf;
	char *tail;
	while (0 != *res && (' ' == *res || '\t' == *res || '\n' == *res || '\r' == *res)) {
		res++;
	}
	tail = res + strlen(res);
	while (tail > res && (' ' == *tail || '\t' == *tail || '\n' == *tail || '\r' == *tail || 0 == *tail)) {
		*tail = 0;
		tail--;
	}
	return res;
} /* trim */

int load(char *filename, t_ctxt **head) {
	FILE	*fp = fopen(filename, "r");
	t_ctxt	*cur_ctx, *new_ctx;
	t_query	*cur_query, *new_query;
	t_answer	*cur_ans, *new_ans;
	char	buf[MAX_ROW];
	char	*line;
	int	num_ctxts = 0;
	int	num_queries = 0;
	int	num_answers = 0;
	char 	*token;
	int 	nline = 0;

	if (NULL == fp) {
		return 0;
	}
	do {	/* loop on contexts */
		do {
			fgets(buf, MAX_ROW, fp);
			nline++;
			line = trim(buf);
		} while (!feof(fp) && '#' == line[0]);
		if (feof(fp)) {
			break;
		}
		new_ctx = malloc(sizeof(t_ctxt));
		new_ctx->queries = NULL;
		num_queries = 0;
		do {	/* loop on queries */
/*
fprintf(stderr, "%s<", line);
*/
			new_query = malloc(sizeof(t_query));
			new_query->answers = NULL;
			token = strtok(line, SEP);
			if (NULL == token) {
				fprintf(stdout, "Error reading line %d\n", nline);
				exit(1);
			}
			strcpy(new_query->text, token);
			num_answers = 0;
			token = strtok(NULL, SEP);
			while (NULL != token) { /* loop on answers */
				new_ans = malloc(sizeof(t_answer));
				strcpy(new_ans->text, token);
				if (NULL == new_query->answers) {
					new_ans->next = NULL;
				} else {
					new_ans->next = new_query->answers;
				}
				new_query->answers = new_ans;
				num_answers++;
				token = strtok(NULL, SEP);
			}
			new_query->num_answers = num_answers;
/*
fprintf(stderr, "ans: %d\n", num_answers);
*/
			if (NULL == new_ctx->queries) {
				new_query->next = NULL;
			} else {
				new_query->next = new_ctx->queries;
			}
			new_ctx->queries = new_query;
			num_queries++;
			do {
				fgets(buf, MAX_ROW, fp);
				nline++;
				line = trim(buf);
			} while (!feof(fp) && '#' == line[0]);
		} while(!feof(fp) && 0!=line[0]);
		new_ctx->num_queries = num_queries;
/*
fprintf(stderr, "queries: %d\n", num_queries);
*/
		if (NULL == *head) {
			new_ctx->next = NULL;
		} else {
			new_ctx->next = *head;
		}
		*head = new_ctx;
		num_ctxts++;
	} while (!feof(fp));
	fclose(fp);
	return num_ctxts;
} /* load */
