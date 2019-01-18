/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstpoint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:18:32 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:13:20 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vlist	*ft_vlstpoint(void *content, size_t channel)
{
	t_vlist *new;

	new = (t_vlist *)ft_vhmemalloc(sizeof(t_vlist), channel);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->content = content;
	return (new);
}