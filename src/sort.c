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
	ft_printf("Comparing string1: %s, string 2: %s\n", first->content, second->content);
	return (ft_strcmp(first->content, second->content));
}

t_vlist	*swap(t_vlist *first, t_vlist *second)
{
	t_vlist *swap;

	swap = second;
	swap->prev = first->prev;
	first->next = swap->next;
	swap->next = first;
	first->prev = swap;
	return (swap);
}

void	head_check(t_vhead **head)
{
	t_vlist *tmp;

	tmp = (*head)->first;
	//if (tmp->first->next)
}

void	ft_sortbubblechar(t_vhead **head)
{
	ft_printf("Sort bubblechar\n");
	if ((*head) == NULL)
		return;
	ft_printf("Bubble sorting...\n");
	head_check(head);
}