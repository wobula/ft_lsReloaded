/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vlstmap.c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 16:00:15 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:14:08 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vlist	*ft_vlstmap(t_vlist *lst, t_vlist *(*f)(t_vlist *))
{
	t_vlist *blah;

	if (lst)
	{
		blah = f(lst);
		blah->next = ft_vlstmap(lst->next, f);
		return (blah);
	}
	return (NULL);
}