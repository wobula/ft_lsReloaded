#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <errno.h>
#include <stdlib.h>
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

#define OPT_L(x) (x[108] == true) ? true : false
#define OPT_R(x) (x[82] == true) ? true : false
#define FILE_OR_FOLDER(x) (x[0]) == 'd' ? true : false

typedef struct s_args 		t_args;
typedef struct s_padding	t_padding;

struct 					s_args 
{
	size_t				files;
	size_t				folders;
	int					opt_count;
	int					arg_count;
	int 				argc;
	char				**args;
	char				**argv;
	t_vhead				*sorted_files;
	t_vhead				*sorted_folders;
	bool				opts[127];
};

struct 					s_padding
{
	int 				file_name;
	int 				owner;
	int 				group;
	int 				file_size;
	int 				links;
	long long			blocks;
};

int 					preprocessor(t_args *meta, char **argv, int argc);
int						processor(t_args *meta);
void					postprocessor();

bool					get_folder_data(bool opts[], char *path);
bool					print_wide(t_padding *info, char *full_path, char *file);
bool					print_boring(t_padding *info, char *full_path, char *file);
void					ft_sortbubblechar(t_vhead **head);
char					*construct_path(char *path, char *file);
void					evaluate_file(t_padding *info, char *path, char *filename);

void					ft_sortbubblechar_alt(t_vhead **head);

void					get_padding_info(t_vhead *head, t_padding *info, char *path);