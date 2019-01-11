/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vhmemalloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguiulfo <gguiulfo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/24 08:21:08 by gguiulfo          #+#    #+#             */
/*   Updated: 2017/11/22 14:15:18 by gguiulfo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_vhmemalloc(size_t size, size_t channel)
{
	void	*ptr;

	ptr = ft_vhmalloc(size, channel);
	ft_bzero(ptr, size);
	return (ptr);
}