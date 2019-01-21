/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static int 	order_check(t_vlist *first, t_vlist *second)
{
	return (ft_strcmp(first->content, second->content));
}

static t_vlist	*swap(t_vlist *first, t_vlist *second)
{
	t_vlist *swap;

	swap = second;
	swap->prev = first->prev;
	(first->prev) ? (first->prev->next = swap) : false;
	first->next = swap->next;
	(swap->next) ? (swap->next->prev = first) : false;
	swap->next = first;
	first->prev = swap;
	return (swap);
}

static t_vlist	*compare(t_vlist *first, bool *sorted)
{
	if (order_check(first, first->next) < 0)
	{
		*sorted = false;
		first = swap(first, first->next);
	}
	return (first);
}

static t_vlist	*bubblemap(t_vlist *lst, t_vlist *(*f)(t_vlist *, bool *), bool *sorted)
{
	t_vlist *blah;

	if (lst->next)
	{
		blah = f(lst, sorted);
		blah->next = bubblemap(blah->next, f, sorted);
		return (blah);
	}
	return (lst);
}

void	ft_sortbubblechar_alt(t_vhead **head)
{
	bool sorted;
	t_vlist *(*f)(t_vlist *, bool *);
	f = &compare;

	sorted = false;
	int x = 0;
	while (sorted == false)
	{
		sorted = true;
		(*head)->first = bubblemap((*head)->first, f, &sorted);
		x++;
		ft_printf("iteration #:%d\n\n", x);
	}
}