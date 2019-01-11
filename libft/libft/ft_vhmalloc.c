/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:03:07 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:13:57 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void		*ft_vhmalloc(size_t size, size_t x)
{
	t_heap_man	*heap_man;
	t_memnode	*new;
	void		*ptr;

	if ((new = malloc(size + sizeof(t_memnode))) == NULL)
		return (NULL);
	ptr = (void *)new + sizeof(t_memnode);
	new->ptr = ptr;
	new->next = NULL;
	heap_man = ft_vget_singleton_node(x);
	if (heap_man->first == NULL)
	{
		heap_man->first = new;
		heap_man->last = new;
		new->next = NULL;
		new->prev = NULL;
	}
	else
	{
		new->prev = heap_man->last;
		heap_man->last->next = new;
		heap_man->last = new;
	}
	return (ptr);
}