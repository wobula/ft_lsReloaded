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
	char *ptr;
	char *ptr2;
	char *ptr3;
	char *ptr4;
	char *ptr5;
	ft_printf("Start\n");
	ptr = (char*)ft_vhmalloc(3, 0);
	ptr2 = ft_vhmalloc(2, 1);
	ptr3 = ft_vhmalloc(100, 10);
	int x = -1;
	while (++x < 98)
	{
		ptr3[x] = 'f';
	}
	ptr[99] = '\0';
	ft_printf("%s\n", ptr3);
	ptr4 = ft_vhmalloc(2, 5);
	ptr5 = ft_vhmalloc(2, 10);
	ft_printf("after malloc\n");
	ptr[0] = 'a';
	ptr[1] = 'b';
	ptr[2] = '\0';
	ft_printf("%s\n", ptr);
	return (0);
}