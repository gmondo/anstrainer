#include <stdio.h>
#define MAX_RESPONSE_LEN 80
/* Try to have context of same size to save program size */
#define MAX_CONTEXT_LEN 3 	

typedef struct query_answers {
	char 	*query;
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
		2, 
		{
			/* Question and answers. All answers in a context must be different */ 
			{"uno", {"un", "one"}},
			{"due", {"deux", "two"}}
		}
	},
	{
		3,
		{
			{"un", {"uno", "one"}},
			{"deux", {"due", "two"}},
			{"trois", {"tre", "three"}}
		}
	},
	{
		2,
		{
			{"one", {"un", "uno"}},
			{"two", {"deux", "due"}}
		}	
	}
};
