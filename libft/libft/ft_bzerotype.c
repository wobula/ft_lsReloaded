/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzerotype.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 21:32:08 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/29 01:13:22 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzerotype(void *s, size_t n, size_t type_size)
{
	unsigned char	*p;
	size_t			counter;
	size_t			full_size;

	p = s;
	full_size = n * type_size;
	counter = -1;
	while (++counter < full_size)
		p[counter] = 0;
}
