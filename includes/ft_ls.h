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
				 	ft_printf("Try 'ls --halp meh' for more information.\n");\

#define INVALID_FILE(x) ft_printf("ls: cannot access '%s': No such file or directory\n", x)

#define OPT_L(x) (x->opts[108]) == true ? true : false
#define OPT_R(x) (x->opts[82]) == true ? true : false
#define VECTOR_FOLDER_CHECK(z) (z->info.folder) == true ? true : false
#define RECURSIVE_CHECK(x, y) ((OPT_R(x)) && VECTOR_FOLDER_CHECK(y)) == true ? true : false
#define FILE_OR_FOLDER(x) (x[0]) == 'd' ? true : false

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
	char				*user;
	char				*group;
	char				*last_mod_eng;
	uid_t				user_id;
	gid_t				group_id;
	off_t				size;
	nlink_t				hlinks;
	time_t				last_modified;
}						t_file;

typedef struct 			s_vec
{
	char				*name;
	char				*path;
	int 				count;
	struct s_file		*info;
	struct s_vec		**vector;
}						t_vec;

bool 					preprocessor(t_args *meta, char **argv, int argc);
int						processor(t_args *meta);

t_file					*get_data(char *path);
void					print_file(t_vec *file);
void					print_data(t_args *meta, t_vec **files);

t_vec					*new_vector(char *path, char *file);
t_vec					**new_vectors(int count);
void					add_to_vector(t_vec *folder, char *path);