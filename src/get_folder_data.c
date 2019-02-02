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

bool		recurse(t_vhead *head, bool opts[])
{
	t_vlist 	*tmp;

	tmp = head->first;
	while (tmp)
	{
		if (tmp->safe == true)
		{
			get_folder_data(opts, tmp->content);
		}
		tmp = tmp->next;
	}
	return (true);
}

DIR 		*get_directory_pointer(char *path)
{
	DIR *dir;

	if (!(dir = opendir(path)))
	{
		ft_printf("ft_ls: cannot open directory '%s': %s\n", path, strerror(errno));
		closedir(dir);
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
	closedir(dir);
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

void		print_folder_contents(t_vhead *head, t_padding *data, bool opts[], char *path)
{
	bool 	(*print)(t_padding *, char *, char *);
	t_vlist *tmp;
	char	*full_path;

	print = (OPT_L(opts) == true) ? &print_wide : &print_boring;
	tmp = head->first;
	while (tmp)
	{
		full_path = construct_path(path, tmp->content);
		tmp->safe = print(data, full_path, tmp->content);
		tmp->content = full_path;
		full_path = NULL;
		tmp = tmp->next;
	}
}

void		get_padding_info(t_vhead *head, t_padding *info, char *path)
{
	t_vlist *tmp;

	tmp = head->first;
	while (tmp)
	{
		evaluate_file(info, path, tmp->content);
		tmp = tmp->next;
	}
}

bool		print_dir(t_vhead *head, t_padding *info, bool opts[], char *path)
{
	if (head->first)
		ft_printf("%s:\n", path);
	ft_printf("total %lld\n", info->blocks);
	print_folder_contents(head, info, opts, path);
	write(1, "\n", 1);
	return (true);
}

void		padding_constructor(t_padding *info)
{
	info->file_size = 0;
	info->file_name = 0;
	info->owner = 0;
	info->group = 0;
	info->links = 0;
	info->blocks = 0;
}

bool		get_folder_data(bool opts[], char *path)
{
	t_padding 	info;
	t_vhead		*head;
	DIR 		*dir;

	padding_constructor(&info);
	if ((dir = get_directory_pointer(path)) == false)
		return (false);
	head = build_directory_structure(dir, path);
	get_padding_info(head, &info, path);
	if (head->first && head->first->next)
		ft_sortbubblechar(&head);
	print_dir(head, &info, opts, path);
	if (OPT_R(opts) == true)
		recurse(head, opts);
	return (true);
}