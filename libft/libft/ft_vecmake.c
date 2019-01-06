/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecmake.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vector	*ft_vecmake(size_t size)
{
	t_vector	*new;
	size_t		x;

	new = ft_memalloc(sizeof(t_vector));
	new->count = size;
	x = 0;
	new->ptrs = (void**)ft_memalloc(sizeof(void*) * (size + 1));
	new->ptrs[size] = 0;
	while (x < size)
	{
		new->ptrs[x] = NULL;
		x++;
	}
	return (new);
}