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

t_vector	*get_file_info(struct stat *sb, char *file)
{
	ft_printf("Get file info here\n");
	return (NULL);
}

t_vector	*get_folder_info(struct stat *sb, char *input)
{
	DIR 	*dir;
	struct 	dirent *dent;
	char 	buffer[50];
	t_vector *folder = NULL;

	strcpy(buffer, input);
	dir = opendir(buffer);
	if(dir != NULL)
	{
		while((dent = readdir(dir)) != NULL)
		{
			ft_printf("Add files to a vector here.\n");
		}
	}
	closedir(dir);
	return (folder);
}

t_vector	*process_arg(char *input)
{
	t_vector *this;
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

void		processor(t_args *meta)
{
	int x;

	x = -1;
	while (++x < meta->arg_count)
	{
		ft_printf("Getting arg: %s\n", meta->args[x]);
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