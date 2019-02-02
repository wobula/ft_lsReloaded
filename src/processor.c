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

static void	process_files(t_vhead *head, bool opts[])
{
	t_vlist *tmp;
	t_padding data;
	bool (*print)(t_padding *, char*, char*);

	get_padding_info(head, &data, NULL);
	print = (OPT_L(opts) == true) ? &print_wide : &print_boring;
	tmp = head->first;
	while (tmp)
	{
		print(&data, tmp->content, tmp->content);
		tmp = tmp->next;
	}
}

static void	process_folders(t_args *meta)
{
	t_vlist *tmp;

	tmp = meta->sorted_folders->first;
	while (tmp)
	{
		get_folder_data(meta->opts, tmp->content);
		tmp = tmp->next;
	}
}

static void add_arg(t_vhead **head, char *arg, bool folder)
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

static void	sort_files_from_folders(t_args *meta)
{
	struct stat sb;
	bool		folder;
	int 		x;

	x = -1;
	while (++x < meta->arg_count)
	{
		lstat(meta->args[x], &sb);
		if ((folder = S_ISDIR(sb.st_mode)) == true)
			add_arg(&meta->sorted_folders, meta->args[x], folder);
		else
			add_arg(&meta->sorted_files, meta->args[x], folder);
	}
}

int 		processor(t_args *meta)
{
	sort_files_from_folders(meta);
	(meta->files == 0 && meta->folders == 0) ? get_folder_data(meta->opts, ".") : false;
	(meta->files > 1) ? ft_sortbubblechar(&meta->sorted_files) : false;
	(meta->files > 0) ? process_files(meta->sorted_files, meta->opts) : false;
	(meta->folders > 1) ? ft_sortbubblechar(&meta->sorted_folders) : false;
	(meta->folders > 0) ? process_folders(meta) : false;
	return (0);
}