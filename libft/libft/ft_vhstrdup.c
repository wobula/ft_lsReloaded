/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vhstrdup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:19:48 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/13 12:25:51 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_vhstrdup(char *hstr, size_t channel)
{
	char	*ret;
	size_t	size;
	size_t	i;

	if (!hstr)
		return (NULL);
	size = -1;
	while (hstr[++size])
		;
	ret = (char*)ft_vhmemalloc(sizeof(char) * (size + 1), channel);
	ret[size] = '\0';
	i = -1;
	while (++i < size)
		ret[i] = hstr[i];
	return (ret);
}