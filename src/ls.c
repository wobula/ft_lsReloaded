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

t_vector	*get_file_info(struct stat *sb, char *file)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->name = file;
	tmp->folder = false;
	tmp->count = 0;
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
		files->vector[x] = process_arg(meta->args[x]);
	}
}

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

void		print_folder(t_vector *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		print_file(&folder->sub_vector[x]->info);
	}
}

void		print_wide(t_vector *files)
{
	if (files->folder == true)
	{
		print_folder(files);
	}
	else
	{
		print_file(&files->info);
	}
}

void		print_folder_simple(t_vector *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		ft_printf("%s\n", folder->sub_vector[x]->name);
	}
}

void		print_simple(t_vector *file)
{
	if (file->folder == true)
	{
		print_folder_simple(file);
	}
	else
	{
		ft_printf("%s\n", file->name);
	}
}

void		print_data(t_args *meta, t_data *files)
{
	int x;

	x = -1;
	while (++x < files->arg_count)
	{
		if (OPT_L(meta->opts) == true)
		{			
			print_wide(files->vector[x]);
		}
		else
		{
			print_simple(files->vector[x]);
		}
		ft_putchar('\n');
	}
}

bool		processor(t_args *meta)
{
	t_data files;

	processor_constructor(meta, &files);
	get_arg_data(meta, &files);
	print_data(meta, &files);
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