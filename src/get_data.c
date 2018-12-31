/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_perms(t_file *data, mode_t st_mode)
{
	int bits;

	bits = (st_mode & S_IFMT);
	data->protection[0] = TYPE_CHECK(bits);
	data->protection[1] = st_mode & S_IRUSR ? 'r' : '-';
	data->protection[2] = st_mode & S_IWUSR ? 'w' : '-';
	data->protection[3] = st_mode & S_IXUSR ? 'x' : '-';
	data->protection[4] = st_mode & S_IRGRP ? 'r' : '-';
	data->protection[5] = st_mode & S_IWGRP ? 'w' : '-';
	data->protection[6] = st_mode & S_IXGRP ? 'x' : '-';
	data->protection[7] = st_mode & S_IROTH ? 'r' : '-';
	data->protection[8] = st_mode & S_IWOTH ? 'w' : '-';
	data->protection[9] = st_mode & S_IXOTH ? 'x' : '-';
	data->protection[10] = '\0';
	data->folder = data->protection[0] == 'd' ? true : false;
}

void	get_time(t_file *data, time_t last_mod)
{
	data->last_mod_eng = ctime(&last_mod);
}

void	get_user_details(t_file *data, uid_t user_id, gid_t group_id)
{
	struct passwd 	*pwd;
	struct group 	*gwd;

	pwd = getpwuid(user_id);
	gwd = getgrgid(group_id);
	data->user = pwd->pw_name;
	data->group = gwd->gr_name;
}

void	get_size(t_file *data, off_t size)
{
	data->size = size;
}

void	get_links(t_file *data, nlink_t hlinks)
{
	data->hlinks = (long long)hlinks;
}

void	get_file_name(t_file *data, char *file)
{
	char *ptr;

	ptr = ft_strchrrev(file, '\\');
	data->file = (ptr == NULL) ? file : ptr;
}

t_file	get_data(struct stat *sb, char *file)
{
	t_file data;

	get_file_name(&data, file);
	get_perms(&data, sb->st_mode);
	get_time(&data, sb->st_mtime);
	get_user_details(&data, sb->st_uid, sb->st_gid);
	get_size(&data, sb->st_size);
	get_links(&data, sb->st_nlink);
	return (data);
}