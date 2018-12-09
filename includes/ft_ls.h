#include <sys/stat.h>
#include <dirent.h>
#include "../libft/includes/libft.h"

#define OPT_CHECK(x)\
				 (x) == 't' ? true :\
				 (x) == 'R' ? true :\
				 (x) == 'a' ? true :\
				 (x) == 'r' ? true :\
				 (x) == 't' ? true : false\

#define INVALID_OPT(x)\
				 	ft_printf("ls invalid option -- '%c'\n", x);\
				 	ft_printf("Try 'ls --dumbass' for more information.\n");\

typedef struct 	s_args 
{
	int 		argc;
	int			opt_count;
	int			arg_count;
	char** 		argv;
	char**		args;
	bool		opts[127];
} 				t_args;