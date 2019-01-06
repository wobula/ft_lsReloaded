/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_vector	*get_dir_contents(t_vector *folder)
{
	DIR 			*dir;
	struct dirent 	*dent;

	dir = opendir(folder->path);
	if (dir != NULL)
	{
		while ((dent = readdir(dir)) != NULL)
		{
			add_to_vector(folder, dent->d_name);
		}
	}
	closedir(dir);
	return (folder);
}

t_vector **get_args(t_args *meta)
{
	t_vector **new;
	int x;

	new = new_vectors(meta->arg_count);
	x = -1;
	while (++x < meta->arg_count)
	{
		new[x] = new_vector(NULL, meta->args[x]);
	}
	return (new);
}

int 	processor(t_args *meta)
{
	t_vector **files;
	int x;

	files = get_args(meta);
	x = -1;
	while (files[++x] != 0)
	{
		get_dir_contents(files[x]);
	}
	print_data(meta, files);
	//if (OPT_R(meta) == true)
	//{
	//	recursive_mode(files);
	//}
}