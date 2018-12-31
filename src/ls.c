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

void	print_folder(t_file_vector *data)
{
	int x = -1;

	while (++x < data->file_count)
	{
		print_file(&data->vector[x]->info);
	}
}

t_file_vector	*get_file_info(struct stat *sb, char *file)
{
	t_file_vector *this;

	this = make_new_vector(1);
	this->info = get_data(sb, file);
	return (this);
}

t_file_vector	*get_folder_info(struct stat *sb, char *input)
{
	DIR 	*dir;
	struct 	dirent *dent;
	char 	buffer[50];
	t_file_vector *folder;
	t_file_vector *tmp;

	folder = make_new_vector(0);
	strcpy(buffer, input);
	dir = opendir(buffer);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			tmp = get_file_info(sb, dent->d_name);
			folder = add_file_to_vector(folder, tmp);
		}
	}
	closedir(dir);
	return (folder);
}

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
		this = get_folder_info(&sb, input);
	}
	else
	{
		this = get_file_info(&sb, input);
	}

	return (this);
}

t_processor	processor_constructor(t_args *meta)
{
	t_processor file_info;

	file_info.args = meta;
	file_info.x = -1;
	file_info.arg_vector = make_new_vector(0);
	return (file_info);
}

void	get_arg_information(t_processor *file_info)
{
	t_file_vector *tmp;
	struct stat sb;
	int x = -1;
	while (++x < file_info->args->arg_count)
	{
		tmp = process_user_input(file_info->args->args[x]);
		file_info->arg_vector = add_file_to_vector(file_info->arg_vector, tmp);
	}
	ft_printf("file info count: %d\n", file_info->arg_vector->file_count);
}

void		processor(t_args *meta)
{
	t_processor		file_info;
	t_file_vector 	*tmp;
	int x;
	struct stat sb;

	file_info = processor_constructor(meta);
	get_arg_information(&file_info);
	x = -1;
	while (++x < file_info.arg_vector->file_count)
	{
		ft_printf("Printing arg: %s\n", meta->args[x]);
		if (file_info.arg_vector->vector[x]->file_count == 1)
			print_file(&(file_info.arg_vector->vector[x]->info));
		else
		{
			print_folder(file_info.arg_vector->vector[x]);
		}
		ft_printf("\n");
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