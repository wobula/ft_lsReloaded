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
t_vector	*get_file_folder_info(t_args *meta, char *path, char *input);

t_vector	*vector_constructor(int count)
{
	t_vector *files;

	files = (t_vector*)ft_hmalloc(sizeof(t_vector));
	files->vector = (t_vector**)ft_hmalloc(sizeof(t_vector*) * (count + 1));
	files->vector[count] = 0;
	files->count = count;
	return (files);
}

t_vector	*get_file_info(char *path, char *file)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->count = 0;
	tmp->info = get_data(path, file);
	return (tmp);
}

t_vector	*get_dir_contents(t_vector *folder)
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
	ft_printf("1File count for %s is %d\n", folder->info->name, folder->count);
	return (folder);
}

t_vector	*get_folder_info(char *path, char *input)
{
	t_vector 	*folder;

	folder = make_new_vector();
	folder->info = get_data(path, input);
	folder = get_dir_contents(folder);
	ft_printf("2File count for %s is %d\n", folder->info->name, folder->count);
	return (folder);
}

t_vector	*get_file_folder_info(t_args *meta, char *path, char *input)
{
	struct stat sb;
	t_vector 	*files;

	lstat(input, &sb);
	if (S_ISDIR(sb.st_mode) == true)
	{
		files = get_folder_info(path, input);
	}
	else
	{
		files = get_file_info(path, input);
	}
	if (OPT_R(meta) == true)
	{
		//recurse(meta, files);
	}
	return (files);
}

bool		get_args_data(t_args *meta, t_vector *files, char **args)
{
	int x;

	x = -1;
	while (++x < files->count)
	{
		files->vector[x] = get_file_folder_info(meta, NULL, args[x]);
	}
}

bool		processor(t_args *meta)
{
	t_vector *files;

	files = vector_constructor(meta->arg_count);
	get_args_data(meta, files, meta->args);
	print_data(meta, files);
}

int 		main(int argc, char **argv)
{
	t_args 		meta;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);
	return (0);
}