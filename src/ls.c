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

void		print_file(t_file *data)
{
	ft_printf("%s ", data->protection);
	ft_printf("%s ", data->user);
	ft_printf("%s ", data->group);
	ft_printf("%lld ", (long long)data->size);
	ft_printf("%lld ", (long long)data->hlinks);
	ft_printf("%.12s ", data->last_mod_eng + 4);
	ft_printf("%s\n", data->file);
}

t_vector	*get_file_info(struct stat *sb, char *file)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->folder = false;
	tmp->info = get_data(sb, file);
	return (tmp);
}

void		get_dir_contents(struct stat *sb, t_vector *folder)
{
	DIR 			*dir;
	struct dirent 	*dent;
	t_vector		*tmp;

	dir = opendir(folder->name);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			tmp = make_new_vector(dent->d_name, false);
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
	folder->info = get_data(sb, folder->name);
	get_dir_contents(sb, folder);
	return (folder);
}

t_vector	*process_arg(char *input)
{
	t_vector 	*this;
	struct stat sb;

	if (lstat(input, &sb) == -1)
	{
		return (NULL);
	}
	if (S_ISDIR(sb.st_mode) == true)
	{
		this = get_folder_info(&sb, input);
		this->folder = true;
	}
	else
	{
		this = get_file_info(&sb, input);
		this->folder = false;
	}

	return (this);
}

void		processor_constructor(t_args *meta, t_data *files)
{
	files->vector = (t_vector**)ft_hmalloc(sizeof(t_vector*) * meta->arg_count + 1);
	files->vector[meta->arg_count] = 0;
	files->arg_count = meta->arg_count;
}

bool		get_arg_data(t_args *meta, t_data *files)
{
	int x;
	t_vector *tmp;

	x = -1;
	while (++x < files->arg_count)
	{
		ft_printf("Processing file: %s\n", meta->args[x]);
		files->vector[x] = process_arg(meta->args[x]);
	}
}

bool		processor(t_args *meta)
{
	t_data files;

	processor_constructor(meta, &files);
	get_arg_data(meta, &files);
	int x = -1;
	while (++x < files.arg_count)
	{
		print_file(&files.vector[x]->info);
	}
}

int 		main(int argc, char **argv)
{
	t_args meta;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);
	return (0);
}