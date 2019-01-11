
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vheap_clear.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:04:59 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/12/13 12:17:23 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int		ft_vheap_clear_man(t_heap_man *heap_man)
{
	t_memnode	*memnode;
	t_memnode	*next;

	if (heap_man == NULL)
		return (1);
	memnode = heap_man->first;
	while (memnode != NULL)
	{
		next = memnode->next;
		free(memnode);
		memnode = next;
	}
	heap_man->first = NULL;
	heap_man->last = NULL;
	free(heap_man);
	return (0);
}

int			ft_vheap_clear(void)
{
	t_vheap_man *vheap_man;
	int x;

	vheap_man = ft_vheap_singleton();
	x = -1;
	while (ft_vheap_clear_man(vheap_man->nodes[++x]) == 0)
		;
	free(vheap_man->nodes);
	free(vheap_man);
	return (x);
}