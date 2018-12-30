/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	data->folder = data->protection[0] == 'd' ? true : false;
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
	data->file = (ptr == NULL) ? file : ptr;
}

t_file	get_data(struct stat *sb, char *file)
{
	t_file data;

	get_file_name(&data, file);
	get_perms(&data, sb->st_mode);
	get_time(&data, sb->st_mtime);
	get_user_details(&data, sb->st_uid, sb->st_gid);
	get_size(&data, sb->st_size);
	get_links(&data, sb->st_nlink);
	return (data);
}

t_file_vector	*make_new_vector(int file_count)
{
	t_file_vector	*files;

	files = (t_file_vector*)ft_hmalloc(sizeof(t_file_vector));
	files->file_count = file_count;
	if (file_count > 0)
	{
		files->vector = (t_file_vector**)ft_hmalloc(sizeof(t_file_vector*) * (file_count + 1));
	}
	else
	{
		files->vector = NULL;
	}
	return (files);
}

t_file_vector	*get_file_info(struct stat *sb, char *file)
{
	t_file_vector *this;

	this = make_new_vector(0);
	this->info = get_data(sb, file);
	return (this);
}

/*void			get_folder_info(t_file *data, struct stat *sb, char *input)
{
	DIR 	*dir;
	struct 	dirent *dent;
	char 	buffer[50];

	strcpy(buffer, input);
	dir = opendir(buffer);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			get_file_info(sb, dent->d_name);
		}
	}
	closedir(dir);
}*/

t_file_vector	*process_user_input(char *input)
{
	t_file_vector *this;
	struct stat sb;

	if (lstat(input, &sb) == -1)
	{
		return (NULL);
	}
	if (S_ISDIR(sb.st_mode) == true)
	{
		//get_folder_info(&data, &sb, input);
	}
	else
	{
		this = get_file_info(&sb, input);
	}

	return (this);
}

void		add_file_to_vector(t_file_vector *vector, t_file_vector *file)
{

}

t_processor	processor_constructor(t_args *meta)
{
	t_processor file_info;

	file_info.args = meta;
	file_info.x = -1;
	file_info.arg_vector = make_new_vector(file_info.args->arg_count);
	return (file_info);
}

void	processor(t_args *meta)
{
	t_processor	file_info;
	t_file_vector *tmp;
	int x;
	struct stat sb;

	file_info = processor_constructor(meta);
	x = -1;
	while (meta->args[++x] != 0)
	{
		ft_printf("Processing file: %s\n", meta->args[x]);
		tmp = process_user_input(meta->args[x]);

		//ft_printf("\n");
	}
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