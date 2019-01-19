#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
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
				 	ft_printf("ft_ls invalid option -- '%c'\n", x);\
				 	ft_printf("Try 'ft_ls --halp meh' for more information.\n");\

#define INVALID_FILE(x) ft_printf("ft_ls: cannot access '%s': No such file or directory\n", x)
#define NO_FOLDER_ACCESS(x) ft_printf("ft_ls: cannot open directory '%s': Permission denied\n", x);

#define OPT_L(x) (x->opts[108]) == true ? true : false
#define OPT_R(x) (x->opts[82]) == true ? true : false
#define FILE_OR_FOLDER(x) (x[0]) == 'd' ? true : false

typedef struct s_args 		t_args;
typedef struct s_file 		t_file;
typedef struct s_vec		t_vec;
typedef struct s_file_pad 	t_file_pad;
typedef struct s_max_pad	t_max_pad;

struct 					s_args 
{
	int 				argc;
	int					opt_count;
	int					arg_count;
	char 				**argv;
	char				**args;
	t_vhead				*sorted_files;
	t_vhead				*sorted_folders;
	bool				opts[127];
};

struct 					s_file
{
	char				protection[11];
	char				*full_path;
	char				*owner;
	char				*group;
	char				*last_mod_eng;
	uid_t				user_id;
	gid_t				group_id;
	long long			size;
	long				hlinks;
	time_t				last_modified;
	t_file_pad			*this;
};

struct		 			s_file_pad
{
	size_t 				user_pad;
	size_t 				group_pad;
	size_t 				file_size_pad;
	size_t  			digit_count;
};

struct 					s_max_pad
{
	size_t				user_pad;
	size_t				group_pad;
	size_t				file_size_length;
	size_t				digit_count;
};

bool 					preprocessor(t_args *meta, char **argv, int argc);
int						processor(t_args *meta);
void					postprocessor(t_args *meta);

char					*get_file_data(char *path, char *file);
bool					get_folder_data(char *path);


void					ft_sortbubblechar(t_vhead **head);