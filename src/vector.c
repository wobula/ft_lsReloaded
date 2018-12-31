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

void	add_to_vector(t_vector *folder, t_vector *add)
{
	t_vector tmp;
	int x;

	tmp.sub_vector = (t_vector**)ft_hmalloc(sizeof(t_vector*) * (folder->count + 1 + 1));
	tmp.sub_vector[folder->count + 1] = 0;
	x = -1;
	while (++x < folder->count)
	{
		tmp.sub_vector[x] = folder->sub_vector[x];
	}
	tmp.sub_vector[x] = add;
	folder->sub_vector = tmp.sub_vector;
	folder->count++;
}

t_vector 	*make_new_vector(char *name, bool folder)
{
	t_vector *tmp;

	tmp = (t_vector*)ft_hmalloc(sizeof(t_vector));
	tmp->name = name;
	tmp->folder = folder;
	tmp->sub_vector = NULL;
	tmp->count = 0;
	return (tmp);
}