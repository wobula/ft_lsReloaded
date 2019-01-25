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

static void	process_files(t_args *meta)
{
	t_vlist *tmp;
	t_padding info;
	bool (*print)(t_padding *, char*, char*);
//get_padding_info(data->head, &data->info, data->path);
	get_padding_info(meta->sorted_files, &info, NULL);
	print = (OPT_L(meta) == true) ? &print_wide : print_boring;
	tmp = meta->sorted_files->first;
	while (tmp)
	{
		print(&info, tmp->content, tmp->content);
		tmp = tmp->next;
	}
}

static void	process_folders(t_args *meta)
{
	t_vlist *tmp;

	tmp = meta->sorted_folders->first;
	while (tmp)
	{
		get_folder_data(meta, tmp->content);
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

static void	sort_folders(t_args *meta)
{
	ft_sortbubblechar(&meta->sorted_folders);
}

static void	sort_files(t_args *meta)
{
	ft_sortbubblechar(&meta->sorted_files);
}

static void	no_args(t_args *meta)
{
	get_folder_data(meta, ".");
}

typedef void (*process)(t_args*);

static void	processor_constructor(t_args *meta, process function[])
{
	int x;

	ft_bzerotype(function, 6, sizeof(process*));
	x = -1;
	if (meta->arg_count == 0)
	{
		function[++x] = &no_args;
		return;
	}
	function[++x] = &sort_files_from_folders;
	function[++x] = (meta->files > 0) ? &sort_files : NULL;
	function[++x] = (meta->files > 0) ? &process_files : NULL;
	function[++x] = (meta->folders > 0) ? &sort_folders : NULL;
	function[++x] = (meta->folders > 0) ? &process_folders : NULL;
}

int 		processor(t_args *meta)
{
	process function[6];
	int 	x;

	processor_constructor(meta, function);
	x = -1;
	while (++x < 6)
	{
		if (function[x] != NULL)
			function[x](meta);
	}
	return (0);
}