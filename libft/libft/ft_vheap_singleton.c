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

static t_heap_man	**ft_vecmemmake(size_t size)
{
	t_heap_man	**new;
	size_t		x;

	x = 0;
	new = (t_heap_man**)ft_memalloc(sizeof(t_heap_man*) * (size + 1));
	while (x < size)
	{
		new[x] = (t_heap_man*)malloc(sizeof(t_heap_man));
		new[x]->first = NULL;
		new[x]->last = NULL;
		x++;
	}
	return (new);
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

void		ft_vecmemexpand(t_vheap_man **vheap_man, size_t get)
{
	t_heap_man **heap_man;
	size_t x;
	size_t total;

	ft_printf("Inside vecmemexpand\n");
	total = (get - (*vheap_man)->count + 1) + (*vheap_man)->count;
	ft_printf("count: %d\n", (*vheap_man)->count);
	ft_printf("get: %d\n", get);
	ft_printf("total: %d\n", total);
	heap_man = (t_heap_man**)ft_memalloc(sizeof(t_heap_man*) * (total + 1));
	heap_man[total] = 0;
	x = 0;
	while (x < (*vheap_man)->count)
	{
		heap_man[x] = (*vheap_man)->nodes[x];
		x++;
	}
	ft_printf("after first while loop\n");
	while (x < total)
	{
		ft_printf("x: %d\n", x);
		heap_man[x] = (t_heap_man*)ft_memalloc(sizeof(t_vheap_man));
		heap_man[x]->first = NULL;
		heap_man[x]->last = NULL;
		x++;
	}
	free((*vheap_man)->nodes);
	(*vheap_man)->nodes = heap_man;
	(*vheap_man)->count = total;
	ft_printf("finished vecmemexpand\n");
}

t_heap_man *ft_vget_singleton(size_t vector)
{
	t_vheap_man *vheap_man;

	vheap_man = ft_vheap_singleton();
	if (vheap_man->nodes == NULL)
	{
		vheap_man->nodes = ft_vecmemmake(vector + 1);
		vheap_man->count = vector + 1;
		return (vheap_man->nodes[vector]);
	}
	if (vheap_man->count <= vector)
	{
		ft_vecmemexpand(&vheap_man, vector);
	}
	ft_printf("vheap man count: %d\n", vheap_man->count);
	ft_printf("get vector: %d\n", vector);
	return (vheap_man->nodes[vector]);
}