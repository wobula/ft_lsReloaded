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
	processor(&meta);
	postprocessor(&meta);*/
	t_hsh *new_table;
	char *ptr = ft_strdup("Supdog");
	char *ptr2 = ft_strdup("hi");

	new_table = ft_hshnew(10, sizeof(char*));
	ft_hshadd(new_table, (void*)ptr);
	//ft_hshprint(new_table);
	ft_hshremove(new_table, (void*)ptr);
	ft_printf("\n\n");
	ft_hshprint(new_table);
	return (0);
}