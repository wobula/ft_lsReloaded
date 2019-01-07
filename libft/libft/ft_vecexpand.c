/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecexpand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_vecexpand(t_vector **this, size_t count)
{
	void		**ptrs;
	size_t		total;
	size_t		x;

	total = (*this)->count + count;
	ptrs = (void**)ft_memalloc(sizeof(void*) * (total + 1));
	ptrs[total] = 0;
	x = 0;
	do 
	{
		ptrs[x] = (*this)->ptrs[x];
	}
	while (++x < (*this)->count);
	do
	{
		ptrs[x] = NULL;
	} while (++x < total);
	free((*this)->ptrs);
	(*this)->count = total;
	(*this)->ptrs = ptrs;
}