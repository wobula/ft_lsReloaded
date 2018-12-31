#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include "../libft/includes/libft.h"

#define OPT_CHECK(x)\
				 (x) == 't' ? true :\
				 (x) == 'R' ? true :\
				 (x) == 'a' ? true :\
				 (x) == 'r' ? true :\
				 (x) == 'l' ? true :\
				 (x) == 't' ? true : false\

#define TYPE_CHECK(x)\
				 (x) == S_IFDIR ? 'd' :\
				 (x) == S_IFREG ? '-' :\
				 (x) == S_IFLNK ? 'l' :\
				 (x) == S_IFSOCK ? 's' :\
				 (x) == S_IFIFO ? 'f' :\
				 (x) == S_IFCHR ? 'c' : 'b'\

#define INVALID_OPT(x)\
				 	ft_printf("ls invalid option -- '%c'\n", x);\
				 	ft_printf("Try 'ls --dumbass' for more information.\n");\

#define OPT_L(x) (x[108]) == true ? true : false\

typedef struct 			s_args 
{
	int 				argc;
	int					opt_count;
	int					arg_count;
	char** 				argv;
	char**				args;
	bool				opts[127];
} 						t_args;

typedef struct 			s_file
{
	bool				valid;
	bool				folder;
	char				protection[11];
	char				*file;
	char				*user;
	char				*group;
	char				*last_mod_eng;
	uid_t				user_id;
	gid_t				group_id;
	off_t				size;
	nlink_t				hlinks;
	time_t				last_modified;
}						t_file;

typedef struct 			s_data
{
	int 				arg_count;
	struct s_vector 	**vector;		
}						t_data;

typedef struct 			s_vector
{
	bool				invalid;
	bool				folder;
	int 				count;
	char				*name;
	struct s_file		info;
	struct s_vector		**sub_vector;
}						t_vector;

bool 					preprocessor(t_args *meta, char **argv, int argc);

t_file					get_data(struct stat *sb, char *file);

t_vector 				*make_new_vector(char *name, bool folder);
void					add_to_vector(t_vector *folder, t_vector *add);