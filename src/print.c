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

/*void		get_padding(t_file *data)
{
	info->user_pad = info->max_user_length - ft_strlen(data->user);
	info->group_pad = info->max_group_length - ft_strlen(data->group);
	info->file_size_pad = info->
}*/

void		print_file(t_vec *file)
{
	//get_padding(file, info);
	ft_printf("%s ", file->info->protection);
	ft_printf("%lld ", (long long)file->info->hlinks);
	ft_printf("%s ", file->info->user);
	ft_printf("%s ", file->info->group);
	ft_printf("%lld ", (long long)file->info->size);

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
	int line_size;

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
	int max_line_size;
	int x;

	x = -1;
	/*if (OPT_L(meta) == true)
		get_padding_info(files);*/
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