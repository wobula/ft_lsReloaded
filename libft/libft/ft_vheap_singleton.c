/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vheap_singleton.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static t_heap_man 	*ft_makeheapman(void)
{
	t_heap_man *new;

	new = (t_heap_man*)ft_memalloc(sizeof(t_heap_man));
	new->first = NULL;
	new->last = NULL;
	return (new);
}

static t_heap_man	**ft_makevheapmen(size_t size)
{
	t_heap_man	**new;
	size_t		x;

	x = 0;
	new = (t_heap_man**)ft_memalloc(sizeof(t_heap_man*) * (size + 1));
	while (x < size)
	{
		new[x] = ft_makeheapman();
		x++;
	}
	return (new);
}

static void		ft_vecmemexpand(t_vheap_man **vheap_man, size_t get)
{
	t_heap_man **heap_man;
	size_t x;
	size_t total;

	total = (get - (*vheap_man)->count + 1) + (*vheap_man)->count;
	heap_man = (t_heap_man**)ft_memalloc(sizeof(t_heap_man*) * (total + 1));
	heap_man[total] = 0;
	x = 0;
	while (x < (*vheap_man)->count)
	{
		heap_man[x] = (*vheap_man)->nodes[x];
		x++;
	}
	while (x < total)
	{
		heap_man[x] = ft_makeheapman();
		x++;
	}
	free((*vheap_man)->nodes);
	(*vheap_man)->nodes = heap_man;
	(*vheap_man)->count = total;
}

t_vheap_man	*ft_vheap_singleton(void)
{
	static t_vheap_man	*vheap_man;

	if (vheap_man == NULL)
	{
		vheap_man = (t_vheap_man*)ft_memalloc(sizeof(t_vheap_man));
		return (vheap_man);
	}
	return (vheap_man);
}

t_heap_man *ft_vget_singleton_node(size_t vector)
{
	t_vheap_man *vheap_man;

	vheap_man = ft_vheap_singleton();
	if (vheap_man->nodes == NULL)
	{
		vheap_man->nodes = ft_makevheapmen(vector + 1);
		vheap_man->count = vector + 1;
		return (vheap_man->nodes[vector]);
	}
	if (vheap_man->count <= vector)
	{
		ft_vecmemexpand(&vheap_man, vector);
	}
	return (vheap_man->nodes[vector]);
}