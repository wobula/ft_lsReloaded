/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vecgetptr_dynamic.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	**ft_vecgetptr_dynamic(t_vector *this, size_t get)
{
	size_t expand;

	if (get < this->count)
		return (this->ptrs[get]);
	expand = get - this->count + 1;
	ft_vecexpand(&this, expand);
	return (&this->ptrs[get]);
}