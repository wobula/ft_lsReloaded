/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"


char		*get_full_path(char *path, char *file)
{
	char *tmp;

	if (path == NULL)
		return (file);
	tmp = ft_hstrjoin(path, "/");
	tmp = ft_hstrjoin(tmp, file);
	return (tmp);
}

t_vec		*new_vector(char *path, char *input)
{
	t_vec 	*file;

	file = (t_vec*)ft_hmalloc(sizeof(t_vec));
	file->name = input;
	file->path = get_full_path(path, input);
	file->info = get_data(file->path);
	file->count = 0;
	file->vector = NULL;
	return (file);
}

t_vec	**new_vectors(int count)
{
	t_vec **files;

	files = (t_vec**)ft_hmalloc(sizeof(t_vec) * (count + 1));
	files[count] = 0;
	return (files);
}

void	increment_vector(t_vec *folder, t_vec *new)
{
	t_vec **subfiles;
	int x;

	x = -1;
	subfiles = new_vectors(folder->count + 1);
	while (++x < folder->count)
	{
		subfiles[x] = folder->vector[x];
	}
	subfiles[x] = new;
	folder->vector = subfiles;
	folder->count++;
}

void	add_to_vector(t_vec *folder, char *input)
{
	t_vec **subfiles;
	t_vec *new;

	new = new_vector(folder->path, input);
	increment_vector(folder, new);
}