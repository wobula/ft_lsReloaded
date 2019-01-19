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

void		recurse(t_vhead *head)
{
	t_vlist *tmp;

	if (!head || !head->first)
		return;
	ft_sortbubblechar(&head);
	tmp = head->first;
	while (tmp)
	{
		get_folder_data(tmp->content);
		tmp = tmp->next;
	}
}

DIR 		*get_directory_pointer(char *path)
{
	DIR *dir;
	int err;

	if (!(dir = opendir(path)))
	{
		err = errno;
		if (err == EACCES)
			NO_FOLDER_ACCESS(path);
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
		ft_vheadaddpoint(&head, dent->d_name, 2);
	}
	return (head);
}

t_vhead		*print_directory_contents(t_vhead *head, char *path)
{
	t_vhead *recursion;
	t_vlist *tmp;
	char	*folder;


	if (!head)
		return (NULL);
	recursion = ft_vheadnew(2);
	tmp = head->first;
	while (tmp)
	{
		if ((folder = get_file_data(path, tmp->content)) != NULL)
		{
			ft_vheadaddpoint(&recursion, folder, 2);
		}
		tmp = tmp->next;
	}
	return (recursion);
}

bool		get_folder_data(char *path)
{
	DIR 			*dir;
	t_vhead			*head;
	t_vhead			*recursion;

	head = NULL;
	ft_printf("%s:\n", path);
	if (!(dir = get_directory_pointer(path)))
		return (false);
	if ((head = build_directory_structure(dir, path))->first == NULL)
		return (false);
	ft_sortbubblechar(&head);
	recursion = print_directory_contents(head, path);
	write(1, "\n", 1);
	closedir(dir);
	recurse(recursion);
	return (true);
}