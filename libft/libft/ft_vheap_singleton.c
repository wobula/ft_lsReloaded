/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vheap_singleton.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/21 21:10:18 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:11:58 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_vheap_man	*ft_vheap_singleton(void)
{
	static t_vheap_man	*vheap_man;

	if (vheap_man == NULL)
		vheap_man = ft_memalloc(sizeof(t_vheap_man));
	return (vheap_man);
}