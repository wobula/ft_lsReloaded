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

void 	process_args(t_args *meta, t_vhead *head, bool folder)
{
	t_vlist *tmp;

	if (!head || !head->first)
		return;
	tmp = head->first;
	while (tmp)
	{
		if (folder == false)
			print_selector(meta, tmp->content, tmp->content);
		else
			get_folder_data(meta, tmp->content);
		tmp = tmp->next;
	}
}

void 	add_arg(t_vhead **head, char *arg, bool folder)
{
	t_vlist *new;

	new = ft_vlstpoint(arg, 2);
	new->safe = folder;
	if ((*head) == NULL)
	{
		(*head) = ft_vheadnew(2);
	}
	ft_vheadaddend(head, new);
}

void 	sort_files_from_folders(t_args *meta)
{
	struct stat sb;
	bool		folder;
	int 		x;

	x = -1;
	while (++x < meta->arg_count)
	{
		lstat(meta->args[x], &sb);
		if ((folder = S_ISDIR(sb.st_mode)) == true)
		{
			add_arg(&meta->sorted_folders, meta->args[x], folder);
		}
		else
		{
			add_arg(&meta->sorted_files, meta->args[x], folder);
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
		process_args(meta, meta->sorted_files, false);
		process_args(meta, meta->sorted_folders, true);
	}
	else
	{
		get_folder_data(meta, ".");
	}
}