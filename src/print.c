/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		print_file(t_vec *file)
{
	ft_printf("%s ", file->info->protection);
	ft_printf("%s ", file->info->user);
	ft_printf("%s ", file->info->group);
	ft_printf("%lld ", (long long)file->info->size);
	//ft_printf("%lld ", (long long)data->hlinks);
	ft_printf("%.12s ", file->info->last_mod_eng + 4);
	ft_printf("%s\n", file->name);
}

void		print_folder(t_vec *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		print_file(folder->vector[x]);
	}
}

void		print_wide(t_vec *file)
{
	if (file->info->folder == true)
	{
		print_folder(file);
	}
	else
	{
		print_file(file);
	}
}

void		print_folder_simple(t_vec *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		ft_printf("%s\n", folder->vector[x]->name);
	}
}

void		print_simple(t_vec *file)
{
	if (file->info->folder == true)
	{
		print_folder_simple(file);
	}
	else
	{
		ft_printf("%s\n", file->name);
	}
}

void		print_data(t_args *meta, t_vec **files)
{
	int x;

	x = -1;
	while (files[++x] != 0)
	{
		if (OPT_L(meta) == true)
		{			
			print_wide(files[x]);
		}
		else
		{
			print_simple(files[x]);
		}
		ft_putchar('\n');
	}
}