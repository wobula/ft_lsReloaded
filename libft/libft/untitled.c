/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_vector.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vector	*ft_make_vector(size_t size)
{
	t_vector	*new;
	int			x;

	new = ft_memalloc(sizeof(t_vector));
	new->count = size;
	x = -1;
	new->ptrs = (void**)ft_memalloc(sizeof(void*) * (size + 1));
	new->ptrs[size] = 0;
	while (++x < size)
	{
		new->ptrs[x] = NULL;
	}
	return (new);
}

t_vector	*ft_add_vector()