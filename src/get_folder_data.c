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

void		print_folder_contents(t_args *meta, t_padding *info, t_vhead *head, char *path)
{
	t_vlist *tmp;
	bool 	(*print)(t_padding *, char *, char *);
	char	*full_path;

	print = (OPT_L(meta) == true) ? &print_wide : &print_boring;
	tmp = head->first;
	while (tmp)
	{
		full_path = construct_path(path, tmp->content);
		tmp->safe = print(info, full_path, tmp->content);
		tmp->content = full_path;
		full_path = NULL;
		tmp = tmp->next;
	}
}

void		padding_constructor(t_padding *info)
{
	info->file_name = 0;
	info->file_size = 0;
	info->owner = 0;
	info->group = 0;
	info->links = 0;
	info->blocks = 0;
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
}

typedef struct s_folder
{
	t_args 		*meta;
	char		*path;
	DIR 		*dir;
	t_vhead 	*head;
	t_padding 	info;
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
	if (data->head && data->head->first && data->head->first->next)
		ft_printf("%s:\n", data->path);
	ft_printf("total %lld\n", data->info.blocks);
	print_folder_contents(data->meta, &data->info, data->head, data->path);
	write(1, "\n", 1);
	return (true);
}

bool		recurse_dir(t_folder *data)
{
	recurse(data->meta, data->head);
	return (true);
}

bool		inspect_dir(t_folder *data)
{
	get_padding_info(data->head, &data->info, data->path);
	return (true);
}

typedef bool (*folder)(t_folder*);

void		folder_constructor(t_args *meta, t_folder *data, folder f[], char *path)
{
	data->meta = meta;
	data->path = path;
	data->dir = NULL;
	data->head = NULL;
	data->info.file_size = 0;
	data->info.owner = 0;
	data->info.group = 0;
	data->info.links = 0;
	data->info.blocks = 0;
	f[0] = &get_dir;
	f[1] = &build_dir;
	f[2] = &sort_dir;
	f[3] = (OPT_L(meta)) ? &inspect_dir : NULL;
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