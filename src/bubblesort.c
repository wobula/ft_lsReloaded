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

int 	order_check(t_vlist *first, t_vlist *second)
{
	return (ft_strcmp(first->content, second->content));
}

t_vlist	*swap(t_vlist *first, t_vlist *second)
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

bool	body_check(t_vhead **head)
{
	t_vlist *tmp;
	bool	sorted;

	sorted = true;
	tmp = (*head)->first->next;
	while (tmp->next)
	{
		if (order_check(tmp, tmp->next) > 0)
		{
			sorted = false;
			tmp = swap(tmp, tmp->next);
		}
		tmp = tmp->next;
	}
	return (sorted);
}

void	head_check(t_vhead **head)
{
	t_vlist *tmp;

	tmp = (*head)->first;
	if (order_check(tmp, tmp->next) > 0)
	{
		(*head)->first = swap(tmp, tmp->next);
	}
}

void	ft_sortbubblechar(t_vhead **head)
{
	bool sorted;

	if ((*head)->first->next == NULL)
		return;
	sorted = false;
	while (sorted == false)
	{
		head_check(head);
		sorted = body_check(head);
	}
}