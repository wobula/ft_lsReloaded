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

t_vector	*process_arg(char *input);

void		processor_constructor(t_args *meta, t_vector *files)
{
	files->vector = (t_vector**)ft_hmalloc(sizeof(t_vector*) * meta->arg_count + 1);
	files->vector[meta->arg_count] = 0;
	files->count = meta->arg_count;
}

t_vector	*get_file_info(char *path, char *file)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->count = 0;
	tmp->info = get_data(path, file);
	return (tmp);
}

void		get_dir_contents(t_vector *folder)
{
	DIR 			*dir;
	struct dirent 	*dent;
	t_vector		*tmp;
	char			*path;

	path = (folder->info->path == NULL) ? folder->info->name : folder->info->path;
	dir = opendir(path);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			tmp = make_new_vector();
			tmp = get_file_info(folder->info->path, dent->d_name);
			add_to_vector(folder, tmp);
		}
	}
	closedir(dir);
}

t_vector	*get_folder_info(char *path, char *input)
{
	t_vector 	*folder;

	folder = make_new_vector();
	folder->info = get_data(path, input);
	get_dir_contents(folder);
	return (folder);
}

t_vector	*get_file_folder_info(char *path, char *input)
{
	struct stat sb;
	char		*file;

	lstat(input, &sb);
	if (S_ISDIR(sb.st_mode) == true)
	{
		return (get_folder_info(path, input));
	}
	return (get_file_info(path, input));
}

bool		get_args_data(t_vector *files, char **args)
{
	int 		x;

	x = -1;
	while (++x < files->count)
	{
		files->vector[x] = get_file_folder_info(NULL, args[x]);
	}
}

bool		processor(t_args *meta, t_vector *files)
{
	processor_constructor(meta, files);
	get_args_data(files, meta->args);
	print_data(meta, files);
}

int 		main(int argc, char **argv)
{
	t_args 		meta;
	t_vector 	files;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta, &files);
	return (0);
}