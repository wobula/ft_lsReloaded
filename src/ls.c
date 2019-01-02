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

t_vector	*get_file_info(struct stat *sb, char *file)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->count = 0;
	tmp->info = get_data(sb, file);
	return (tmp);
}

void		get_dir_contents(struct stat *sb, t_vector *folder)
{
	DIR 			*dir;
	struct dirent 	*dent;
	t_vector		*tmp;

	dir = opendir(folder->info.name);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			tmp = make_new_vector();
			tmp->info = get_data(sb, dent->d_name);
			add_to_vector(folder, tmp);
		}
	}
	closedir(dir);
}

t_vector	*get_folder_info(struct stat *sb, char *input)
{
	t_vector 	*folder;

	folder = make_new_vector(input, true);
	folder->info = get_data(sb, input);
	get_dir_contents(sb, folder);
	return (folder);
}

t_vector	*get_file_folder_info(char *input)
{
	struct stat sb;

	lstat(input, &sb);
	if (S_ISDIR(sb.st_mode) == true)
	{
		return (get_folder_info(&sb, input));
	}
	return (get_file_info(&sb, input));
}

void		recurse(t_vector *folder)
{
	ft_printf("Inside recurse\n");
	int x = -1;
	ft_printf("Outside recurse\n");
}

bool		get_args_data(t_vector *files, char **args)
{
	int 		x;

	x = -1;
	while (++x < files->count)
	{
		files->vector[x] = get_file_folder_info(args[x]);
	}
}

bool		processor(t_args *meta, t_vector *files)
{
	processor_constructor(meta, files);
	get_args_data(files, meta->args);
	if ((OPT_R(meta)) == true)
	{
		ft_printf("RECURSIVE MODE ON\n");
		//get_recurse_data();
	}
	//print_data(meta, files);
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