#define MAX_STR	64
#define MAX_ANS 5
#define MAX_ROW 1024
#define DEF_FIN "anstrainer.txt"
#define SEP     "?|"

typedef struct answer {
	char		text[MAX_STR];
	struct answer	*next;
} t_answer;

typedef struct query {
	char 		text[MAX_STR];
	int		num_answers;
	t_answer	*answers;
	struct query	*next;
} t_query;

/* Context are set of t_qa with similar responses */
typedef struct context {
	int		num_queries;
	t_query		*queries;
	struct context	*next;
} t_ctxt;

int load(char *, t_ctxt **);
void make_query(t_ctxt *, int, char *);
