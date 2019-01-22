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
	bool 	(*print)(char *, char *);
	char	*full_path;

	print = (OPT_L(meta) == true) ? &print_wide : &print_boring;
	tmp = head->first;
	while (tmp)
	{
		full_path = construct_path(path, tmp->content);
		tmp->safe = print(full_path, tmp->content);
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
	long long	blocks;
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
	info->blocks += (long long)sb.st_blocks;
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

typedef struct s_folder
{
	t_args 		*meta;
	char		*path;
	DIR 		*dir;
	t_vhead 	*head;
	t_padding 	spacing;
}				t_folder;

bool		sort_dir(t_folder *data)
{
	if (data->head->first != NULL)
		ft_sortbubblechar(&data->head);
	return (true);
}

bool		build_dir(t_folder *data)
{
	data->head = build_directory_structure(data->dir, data->path);
	return (true);
}

bool		get_dir(t_folder *data)
{
	data->dir = get_directory_pointer(data->path);
	if (data->dir == NULL)
		return (false);
	return (true);
}

bool		print_dir(t_folder *data)
{
	print_folder_contents(data->meta, data->head, data->path);
	return (true);
}

bool		recurse_dir(t_folder *data)
{
	recurse(data->meta, data->head);
	return (true);
}

typedef bool (*folder)(t_folder*);

void		folder_constructor(t_args *meta, t_folder *data, folder f[], char *path)
{
	data->meta = meta;
	data->path = path;
	data->dir = NULL;
	data->head = NULL;
	data->spacing.file_size = 0;
	data->spacing.owner = 0;
	data->spacing.group = 0;
	data->spacing.links = 0;
	f[0] = &get_dir;
	f[1] = &build_dir;
	f[2] = &sort_dir;
	f[3] = (OPT_L(meta)) ? NULL : NULL; //&inspect_dir
	f[4] = &print_dir;
	f[5] = (OPT_R(meta)) ? &recurse_dir : NULL;
	f[6] = NULL;
}

bool		get_folder_data(t_args *meta, char *path)
{
	t_folder 	data;
	folder 		function[8];
	int 		x;

	folder_constructor(meta, &data, function, path);
	x = -1;
	while (++x < 7)
	{
		if (function[x] != NULL)
		{
			if (function[x](&data) == false)
				return (false);
		}
	}
	return (true);
}