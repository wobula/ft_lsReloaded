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

t_file_vector	*add_file_to_vector(t_file_vector *folder, t_file_vector *file)
{
	t_file_vector 	*new;
	int 			x;

	new = make_new_vector(folder->file_count + 1);
	x = -1;
	while (++x < folder->file_count)
	{
		new->vector[x] = folder->vector[x];
	}
	new->vector[x] = file;
	new->file_count = folder->file_count + 1;
	return (new);
}