#include <stdio.h>
#define MAX_RESPONSE_LEN 80
/* try to have context of same size to save program size*/
#define MAX_CONTEXT_LEN 3 	

typedef struct query_answers {
	char 	*query;
	char 	*answers[MAX_RESPONSE_LEN];
} t_qa;

/* context are set of t_qr with same response type */
typedef struct context {
	int	size;
	t_qa	query_answers[MAX_CONTEXT_LEN];
} t_ctxt;

t_ctxt contexts[] = {
	{
		2, 
		{
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
