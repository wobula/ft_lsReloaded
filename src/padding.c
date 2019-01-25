/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void		get_file_name(t_padding *info, char *file)
{
	int x;

	x = ft_strlen(file);
	if (x > info->file_name)
		info->file_name = x;
}

typedef struct 		s_ownerinfo
{
	struct passwd 	*pwd;
	struct group	*gwd;
}					t_ownerinfo;

void		get_owner_group(t_padding *info, struct stat *sb)
{
	t_ownerinfo data;
	int 		x;

	data.pwd = getpwuid(sb->st_uid);
	data.gwd = getgrgid(sb->st_gid);
	x = ft_strlen(data.pwd->pw_name);
	if (x > info->owner)
		info->owner = x;
	x = ft_strlen(data.gwd->gr_name);
	if (x > info->group)
		info->group = x;
}

void		get_file_size(t_padding *info, struct stat *sb)
{
	long long size;
	int x;

	size = (long long)sb->st_size;
	x = 0;
	while (size > 0)
	{
		size = size / 10;
		x++;
	}
	if (x > info->file_size)
		info->file_size = x;
}

void		get_link_size(t_padding *info, struct stat *sb)
{
	long	links;
	int		x;

	links = (long)sb->st_nlink;
	x = 0;
	while (links > 0)
	{
		links = links / 10;
		x++;
	}
	if (x > info->links)
		info->links = x;
}

void		evaluate_file(t_padding *info, char *path, char *file)
{
	struct 	stat sb;
	char 	*full_path;

	full_path = construct_path(path, file);
	get_file_name(info, file);
	lstat(full_path, &sb);
	get_owner_group(info, &sb);
	get_file_size(info, &sb);
	get_link_size(info, &sb);
	info->blocks += (long long)sb.st_blocks / 2;
}