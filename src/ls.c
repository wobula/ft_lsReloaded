#include "../includes/ft_ls.h"

void	get_perms(t_file *data, mode_t st_mode)
{
	int bits;

	bits = (st_mode & S_IFMT);
	data->protection[0] = TYPE_CHECK(bits);
	data->protection[1] = st_mode & S_IRUSR ? 'r' : '-';
    data->protection[2] = st_mode & S_IWUSR ? 'w' : '-';
    data->protection[3] = st_mode & S_IXUSR ? 'x' : '-';
    data->protection[4] = st_mode & S_IRGRP ? 'r' : '-';
    data->protection[5] = st_mode & S_IWGRP ? 'w' : '-';
    data->protection[6] = st_mode & S_IXGRP ? 'x' : '-';
    data->protection[7] = st_mode & S_IROTH ? 'r' : '-';
    data->protection[8] = st_mode & S_IWOTH ? 'w' : '-';
    data->protection[9] = st_mode & S_IXOTH ? 'x' : '-';
    data->protection[10] = '\0';
}

void	get_time(t_file *data, time_t last_mod)
{
	data->last_mod_eng = ctime(&last_mod);
}

void	get_user_details(t_file *data, uid_t user_id, gid_t group_id)
{
	struct passwd 	*pwd;
	struct group 	*gwd;

	pwd = getpwuid(user_id);
	gwd = getgrgid(group_id);
	data->user = pwd->pw_name;
	data->group = gwd->gr_name;
}

void	get_size(t_file *data, off_t size)
{
	data->size = size;
}

void	get_links(t_file *data, nlink_t hlinks)
{
	data->hlinks = (long long)hlinks;
}

void	print_file(t_file *data)
{
	ft_printf("%s ", data->protection);
	ft_printf("%s ", data->user);
    ft_printf("%s ", data->group);
    ft_printf("%lld ", (long long)data->size);
    ft_printf("%lld ", (long long)data->hlinks);
    ft_printf("%.12s ", data->last_mod_eng + 4);
    ft_printf("%s\n", data->file);
}

void	get_file_name(t_file *data, char *file)
{
	char *ptr;

	ptr = ft_strchrrev(file, '\\');
	if (ptr == NULL)
	{
		data->file = file;
	}
	else
	{
		data->file = ptr;
	}
}

void	get_file_info(char *file)
{
	struct stat sb;
	t_file data;

	if (lstat(file, &sb) == -1)
	{
		ft_printf("Error");
		return ;
	}
	get_file_name(&data, file);
    get_perms(&data, sb.st_mode);
    get_time(&data, sb.st_mtime);
    get_user_details(&data, sb.st_uid, sb.st_gid);
    get_size(&data, sb.st_size);
    get_links(&data, sb.st_nlink);

    print_file(&data);
}

void	get_folder_info(t_args *meta)
{
    DIR *dir;
    struct dirent *dent;
    char buffer[50];

    strcpy(buffer, meta->args[0]);
    dir = opendir(buffer);   //this part
    if(dir != NULL)
    {
        while((dent = readdir(dir)) != NULL)
            ft_printf("%s\n", dent->d_name);
    }
    closedir(dir);
}

void	processor(t_args *meta)
{
	get_file_info(meta->args[0]);
}

int 	main(int argc, char **argv)
{
	t_args meta;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);
	return (0);
}