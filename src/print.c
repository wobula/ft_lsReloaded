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

void		print_file(t_file *data)
{
	ft_printf("%s ", data->protection);
	ft_printf("%s ", data->user);
	ft_printf("%s ", data->group);
	ft_printf("%lld ", (long long)data->size);
	ft_printf("%lld ", (long long)data->hlinks);
	ft_printf("%.12s ", data->last_mod_eng + 4);
	ft_printf("%s\n", data->name);
}

void		print_folder(t_vector *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		print_file(folder->vector[x]->info);
	}
}

void		print_wide(t_vector *files)
{
	if (files->info->folder == true)
	{
		print_folder(files);
	}
	else
	{
		print_file(files->info);
	}
}

void		print_folder_simple(t_vector *folder)
{
	int x;

	x = -1;
	while (++x < folder->count)
	{
		ft_printf("%s\n", folder->vector[x]->info->name);
	}
}

void		print_simple(t_vector *file)
{
	if (file->info->folder == true)
	{
		print_folder_simple(file);
	}
	else
	{
		ft_printf("%s\n", file->info->name);
	}
}

void		print_data(t_args *meta, t_vector *files)
{
	int x;

	x = -1;
	while (++x < files->count)
	{
		if (OPT_L(meta) == true)
		{			
			print_wide(files->vector[x]);
		}
		else
		{
			print_simple(files->vector[x]);
		}
		ft_putchar('\n');
	}
}