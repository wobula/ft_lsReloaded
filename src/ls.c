/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int 		main(int argc, char **argv)
{
	/*t_args 		meta;

	if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);*/
	t_vector *new;
	int x;
	void **ptr;

	new = ft_vecmake(4);
	x = -1;
	while (++x < 4)
	{
		new->ptrs[x] = ft_strdup("sup");
		ft_printf("%d: %s\n", x, new->ptrs[x]);
	}
	ft_vecexpand(&new, 2);
	ft_printf("%d: %s\n", 1, new->ptrs[1]);
	new->ptrs[4] = ft_strdup("sup");
	new->ptrs[5] = ft_strdup("sup");
	ptr = ft_vecgetptr_dynamic(new, 10);
	new->ptrs[10] = ft_strdup("Hi mom\n");
	ft_printf("expand: %s\n", new->ptrs[10]);
	(*ptr) = (char*)ft_strdup("Yo momma\n");
	x = -1;
	ft_printf("count %d\n", new->count);
	while (++x < new->count)
	{
		if (new->ptrs[x] != NULL)
			ft_printf("%d: %s\n", x, new->ptrs[x]);
		else
			ft_printf("%d: NULL\n", x);
	}
	return (0);
}