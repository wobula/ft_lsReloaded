/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	permissions(char buff[], mode_t st_mode)
{
	int bits;

	bits = (st_mode & S_IFMT);
	buff[0] = TYPE_CHECK(bits);
	buff[1] = st_mode & S_IRUSR ? 'r' : '-';
	buff[2] = st_mode & S_IWUSR ? 'w' : '-';
	buff[3] = st_mode & S_IXUSR ? 'x' : '-';
	buff[4] = st_mode & S_IRGRP ? 'r' : '-';
	buff[5] = st_mode & S_IWGRP ? 'w' : '-';
	buff[6] = st_mode & S_IXGRP ? 'x' : '-';
	buff[7] = st_mode & S_IROTH ? 'r' : '-';
	buff[8] = st_mode & S_IWOTH ? 'w' : '-';
	buff[9] = st_mode & S_IXOTH ? 'x' : '-';
	buff[10] = '\0';
}

typedef struct s_ownerinfo
{
	struct passwd 	*pwd;
	struct group	*gwd;
}				t_ownerinfo;

typedef struct 	s_filepad
{
	int			file_name;
	int			links;
	int			group;
	int			owner;
	int			file_size;
}				t_filepad;

void printpad(int pad)
{
	while (pad > 0)
	{
		write(1, " ", 1);
		pad--;
	}
}

void 	print_data(t_filepad *this, struct stat *sb, char *perms, char *file)
{
	t_ownerinfo data;

	data.pwd = getpwuid(sb->st_uid);
	data.gwd = getgrgid(sb->st_gid);
	ft_printf("%s ", perms);
	ft_printf("%ld ", (long)sb->st_nlink);
	printpad(this->owner);
	ft_printf("%s ", data.pwd->pw_name);
	printpad(this->group);
	ft_printf("%s ", data.gwd->gr_name);
	printpad(this->file_size);
	ft_printf("%lld ", (long long)sb->st_size);
	ft_printf("%.12s ", (ctime(&sb->st_mtime)) + 4);
	ft_printf("%s\n", file);
}

bool	print_boring(t_padding *info, char *full_path, char *file)
{
	struct stat sb;

	if (lstat (full_path, &sb) == -1)
	{
		return (false);
	}
	ft_printf("%s\n", file);
	return (S_ISDIR(sb.st_mode));
}

void	get_this_files_pad(t_filepad *this, t_padding *info, struct stat *sb, char *file)
{
	long long 	size;

	this->file_size = 0;
	size = (long long)sb->st_size;
	while (size > 0)
	{
		size = size / 10;
		this->file_size++;
	}
	this->file_size = info->file_size - this->file_size;
}

void	get_this_group_pad(t_filepad *this, t_padding *info, struct stat *sb)
{
	t_ownerinfo data;
	int 		x;
	int			y;

	data.pwd = getpwuid(sb->st_uid);
	data.gwd = getgrgid(sb->st_gid);
	x = ft_strlen(data.pwd->pw_name);
	y = ft_strlen(data.gwd->gr_name);
	this->group = info->group - y;
	this->owner = info->owner - x;
}

bool	print_wide(t_padding *info, char *full_path, char *file)
{
	char		perms[11];
	struct stat sb;
	t_filepad	this;

	if (lstat(full_path, &sb) == -1)
	{
		return (false);
	}
	get_this_files_pad(&this, info, &sb, file);
	get_this_group_pad(&this, info, &sb);
	permissions(perms, sb.st_mode);
	print_data(&this, &sb, perms, file);
	return (S_ISDIR(sb.st_mode));
}