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
	t_vlist 	*tmp;
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
	if (head->first == NULL)
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

typedef struct s_ownerinfo
{
	struct passwd 	*pwd;
	struct group	*gwd;
}				t_ownerinfo;

/*
	data.pwd = getpwuid(sb->st_uid);
	data.gwd = getgrgid(sb->st_gid);
	ft_printf("%s ", data.pwd->pw_name);
	ft_printf("%s ", data.gwd->gr_name);
*/

void		evaluate_file(t_padding *info, char *path, char *filename)
{
	struct stat sb;
	t_ownerinfo data;
	int 		x;
	long long	size;
	long		links;
	char 		*full_path;

	x = 0;
	full_path = construct_path(path, filename);
	ft_printf("Inside evaluate_file: %s\n", full_path);
	lstat(full_path, &sb);
	if ((x = ft_strlen(full_path) > info->file_name))
		info->file_name = x;
	data.pwd = getpwuid(sb.st_uid);
	data.gwd = getgrgid(sb.st_gid);
	if ((x = ft_strlen(data.pwd->pw_name)) > info->owner)
		info->owner = x;
	if ((x = ft_strlen(data.gwd->gr_name)) > info->group)
		info->group = x;
	size = (long long)sb.st_size;
	x = 0;
	while (size > 0)
	{
		size = size / 10;
		x++;
	}
	if (x > info->file_size)
		info->file_size = x;
	links = (long)sb.st_nlink;
	x = 0;
	while (links > 0)
	{
		links = links / 10;
		x++;
	}
}

void		padding_constructor(t_padding *info)
{
	info->file_size = 0;
	info->owner = 0;
	info->group = 0;
	info->links = 0;
}

void		get_padding_info(t_vhead *head, t_padding *info, char *path)
{
	t_vlist *tmp;

	tmp = head->first;
	ft_printf("Inside get padding info\n");
	padding_constructor(info);
	while (tmp)
	{
		evaluate_file(info, path, tmp->content);
		tmp = tmp->next;
	}
	//ft_printf("Padding results:\n");
	//ft_printf("largest file size: %d\n", info->file_size);
	//ft_printf("largest owner: %d\n", info->owner);
	//ft_printf("largest group: %d\n", info->group);
	//ft_printf("largest links: %d\n", info->links);
}

bool		get_folder_data(t_args *meta, char *path)
{
	DIR 			*dir;
	t_vhead			*head;
	t_padding		info;

	head = NULL;
	ft_printf("%s:\n", path);
	if (!(dir = get_directory_pointer(path)))
		return (false);
	if ((head = build_directory_structure(dir, path))->first == NULL)
		return (false);
	ft_sortbubblechar(&head);
	get_padding_info(head, &info, path);
	print_folder_contents(meta, head, path);
	write(1, "\n", 1);
	closedir(dir);
	if (OPT_R(meta) != false)
		return (recurse(meta, head));
	return (true);
}