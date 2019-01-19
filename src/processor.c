/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processor.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void 	process_files(t_vlist *start)
{
	t_vlist *tmp;

	tmp = start;
	while (tmp)
	{
		get_file_data(NULL, tmp->content);
		tmp = tmp->next;
	}
}

void 	process_folders(t_vlist *start)
{
	t_vlist *tmp;

	tmp = start;
	while (tmp)
	{
		get_folder_data(tmp->content);
		tmp = tmp->next;
	}
}

void 	add_arg(t_vhead **head, char *arg)
{
	t_vlist *new;

	new = ft_vlstpoint(arg, 2);
	if ((*head) == NULL)
	{
		(*head) = ft_vheadnew(2);
	}
	ft_vheadaddend(head, new);
}

void 	sort_files_from_folders(t_args *meta)
{
	struct stat sb;
	int x;

	x = -1;
	while (++x < meta->arg_count)
	{
		lstat(meta->args[x], &sb);
		if (S_ISDIR(sb.st_mode) == true)
		{
			add_arg(&meta->sorted_folders, meta->args[x]);
		}
		else
		{
			add_arg(&meta->sorted_files, meta->args[x]);
		}
	}
}

void 	sort_args(t_args *meta)
{
	sort_files_from_folders(meta);
	if (meta->sorted_files != NULL)
		ft_sortbubblechar(&meta->sorted_files);
	if (meta->sorted_folders != NULL)
		ft_sortbubblechar(&meta->sorted_folders);
}

int 	processor(t_args *meta)
{
	if (meta->arg_count > 0)
	{
		sort_args(meta);
		if (meta->sorted_files != NULL)
		{
			process_files(meta->sorted_files->first);
		}
		if (meta->sorted_folders != NULL)
		{
			process_folders(meta->sorted_folders->first);
		}
	}
	else
	{
		get_folder_data(".");
	}
}