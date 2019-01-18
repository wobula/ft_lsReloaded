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

t_vec	*get_dir_contents(t_vec *folder)
{
	DIR 			*dir;
	struct dirent 	*dent;

	dir = opendir(folder->path);
	if (dir != NULL)
	{
		while ((dent = readdir(dir)) != NULL)
		{
			//add_to_vector(folder, dent->d_name);
			ft_printf("%s\n", dent->d_name);
		}
	}
	closedir(dir);
	return (folder);
}

void process_args(t_args *meta)
{
	ft_printf("TBD: process args\n");
}

void add_arg(t_vhead **head, char *arg)
{
	t_vlist *new;

	new = ft_vlstpoint(arg, 2);
	if ((*head) == NULL)
	{
		(*head) = ft_vheadnew(2);
	}
	ft_vheadaddend(head, new);
}

void sort_files_from_folders(t_args *meta)
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

void print_lst(t_vhead *head, char *file_folder)
{
	t_vlist *tmp;
	if (head == NULL)
		return;
	tmp = head->first;
	while (tmp != NULL)
	{
		ft_printf("%s\n", tmp->content);
		tmp = tmp->next;
	}
	ft_printf("\n");
}

void sort_args(t_args *meta)
{
	sort_files_from_folders(meta);
	print_lst(meta->sorted_files, "files");
	print_lst(meta->sorted_folders, "folders");
	if (meta->sorted_files != NULL)
		ft_sortbubblechar(&meta->sorted_files);
	if (meta->sorted_folders != NULL)
		ft_sortbubblechar(&meta->sorted_folders);
	ft_printf("--Printing Files:\n");
	print_lst(meta->sorted_files, "files");
	ft_printf("--Printing Folders:\n");
	print_lst(meta->sorted_folders, "folders");
}

void	process_sorted_args(t_args *meta)
{
	ft_printf("implement handle sorted args\n");
}

int 	processor(t_args *meta)
{
	if (meta->arg_count > 0)
	{
		sort_args(meta);
		process_sorted_args(meta);
	}
	else
	{
		get_data(".");
	}
}