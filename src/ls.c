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
	ptr = (char*)ft_vhmalloc(3, 0);
	ptr2 = ft_vhmalloc(2, 1);
	ptr3 = ft_vhmalloc(100, 10);
	int x = -1;
	while (++x < 98)
	{
		ptr3[x] = 'f';
	}
	ptr3[99] = '\0';
	ptr[0] = 'a';
	ptr[1] = 'b';
	ptr[2] = '\0';
	ptr5 = ft_vhmalloc(4, 20);
	ptr5[0] = 'r';
	ptr5[1] = 'o';
	ptr5[2] = 'b';
	ptr5[3] = '\0';
	ptr[0] = 'a';
	ptr[1] = 'b';
	ptr[2] = '\0';
	ptr4 = ft_vhmalloc(ft_strlen("Hello world") + 1, 5);
	ptr4[0] = 'h';
	ptr4[1] = 'e';
	ptr4[2] = 'l';
	ptr4[3] = 'l';
	ptr4[4] = 'o';
	ptr4[5] = ' ';
	ptr4[6] = 'w';
	ptr4[7] = 'o';
	ptr4[8] = 'r';
	ptr4[9] = 'l';
	ptr4[10] = 'd';
	ptr4[11] = '\0';
	ft_printf("ptr: %s\n", ptr);
	ft_printf("ptr2: %s\n", ptr2);
	ft_printf("ptr3: %s\n", ptr3);
	ft_printf("ptr4: %s\n", ptr4);
	ft_printf("ptr5: %s\n", ptr5);
	return (0);
}