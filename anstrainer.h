#include <stdio.h>
#define MAX_RESPONSE_LEN 80
/* Try to have context of same size to save program size */
#define MAX_CONTEXT_LEN 4 	

typedef struct query_answers {
	char 	*query;
	int	size;
	char 	*answers[MAX_RESPONSE_LEN];
} t_qa;

/* Context are set of t_qa with same response type */
typedef struct context {
	int	size;
	t_qa	query_answers[MAX_CONTEXT_LEN];
} t_ctxt;

t_ctxt contexts[] = {
	{
		/* Number of questions in the context */
		4,
		{
			/* Question and answers */
			/* First example: questions with single response */
			{"What's the capital of France?", 1, {"Paris"}},
			{"What's the capital of Italy?", 1, {"Rome"}},
			{"What's the capital of Denmark?", 1, {"Copenaghen"}},
			{"What's the capital of Spain?", 1, {"Madrid"}}
		}
	},
	{
		3,
		{
			/* Second example: questions with multiple responses */
			/* Note that same response cannot be written differently, i.e. Germany differs from germany */
			{"In which states flows Danube?", 3, {"Austria", "Romania", "Germany"}},
			{"In which states flows Rhine?", 3, {"Switzerland", "France", "Germany"}},
			{"Which states border Germany?", 4, {"France", "Poland", "Switzerland", "Austria"}} 
		}
	}
};
