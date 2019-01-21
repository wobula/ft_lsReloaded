/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_contents.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"
#include <stdlib.h>

bool		recurse(t_args *meta, t_vhead *head)
{
	t_vlist *tmp;
	struct stat sb;

	if (!head || !head->first)
		return (true);
	tmp = head->first;
	while (tmp)
	{
		if (tmp->safe == true)
		{
			get_folder_data(meta, tmp->content);
		}
		tmp = tmp->next;
	}
	return (true);
}

DIR 		*get_directory_pointer(char *path)
{
	DIR *dir;
	int err;

	if (!(dir = opendir(path)))
	{
		err = errno;
		ft_printf("ft_ls: cannot open directory '%s': %s\n", path, strerror(errno));
		return (NULL);
	}
	return (dir);
}

t_vhead		*build_directory_structure(DIR *dir, char *path)
{
	struct dirent 	*dent;
	t_vhead			*head;
	char			*folder;

	head = ft_vheadnew(2);
	while ((dent = readdir(dir)) != NULL)
	{
		if (dent->d_name[0] == '.')
			continue;
		ft_vheadaddpoint(&head, ft_vhstrdup(dent->d_name, 2), 2);
	}
	return (head);
}

char		*construct_path(char *path, char *file)
{
	char *full_path;

	if (!path)
		return (file);
	if (ft_strcmp(path, "/") == 0)
	{
		full_path = ft_vhstrjoin(path, file, 2);
	}
	else
	{
		full_path = ft_vhstrjoin(path, "/", 2);
		full_path = ft_vhstrjoin(full_path, file, 2);
	}
	return (full_path);
}

void		print_folder_contents(t_args *meta, t_vhead *head, char *path)
{
	t_vlist *tmp;
	char	*full_path;

	tmp = head->first;
	while (tmp)
	{
		full_path = construct_path(path, tmp->content);
		tmp->safe = print_selector(meta, full_path, tmp->content);
		tmp->content = full_path;
		full_path = NULL;
		tmp = tmp->next;
	}
}

bool		get_folder_data(t_args *meta, char *path)
{
	DIR 			*dir;
	t_vhead			*head;

	head = NULL;
	ft_printf("%s:\n", path);
	if (!(dir = get_directory_pointer(path)))
		return (false);
	if ((head = build_directory_structure(dir, path))->first == NULL)
		return (false);
	ft_sortbubblechar(&head);
	print_folder_contents(meta, head, path);
	write(1, "\n", 1);
	closedir(dir);
	if (OPT_R(meta) != false)
		return (recurse(meta, head));
	return (true);
}