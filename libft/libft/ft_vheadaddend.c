/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vheadaddend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_vheadaddend(t_vhead **head, t_vlist *new)
{
	if ((*head)->first == NULL)
	{
		(*head)->first = new;
		(*head)->last = new;
	}
	else
	{
		new->prev = (*head)->last;
		(*head)->last->next = new;
		(*head)->last = new;
	}
}