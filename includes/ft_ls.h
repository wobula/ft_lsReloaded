#include "../libft/includes/libft.h"

#define OPT_CHECK(x)\
				 (x) == 'l' ? true :\
				 (x) == 'R' ? true :\
				 (x) == 'a' ? true :\
				 (x) == 'r' ? true :\
				 (x) == 't' ? true : false\

typedef struct 	s_args 
{
	int 		argc;
	int			opt_count;
	int			arg_count;
	char** 		argv;
	char**		args;
	bool		opts[127];
} 				t_args;