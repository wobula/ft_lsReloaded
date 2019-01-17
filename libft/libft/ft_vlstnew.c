/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstnew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:18:32 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:13:20 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vlist	*ft_vlstnew(void const *content, size_t content_size, size_t channel)
{
	t_vlist *new;

	new = (t_vlist *)ft_vhmemalloc(sizeof(t_vlist), channel);
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	if (content != NULL && content_size != 0)
	{
		new->content = ft_vhmemalloc(content_size, channel);
		if (new->content == NULL)
			return (NULL);
		ft_memcpy(new->content, content, content_size);
		new->content_size = content_size;
	}
	else
	{
		new->content = NULL;
		new->content_size = 0;
	}
	return (new);
}