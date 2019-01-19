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

void	print_list_directories(t_vhead *head)
{
	t_vlist *lst;

	ft_printf("Inside print list directories\n");
	if (head->first == NULL)
		return;
	lst = head->first;
	while (lst)
	{
		ft_printf("->folders: %s\n", lst->content);
		lst = lst->next;
	}
}

void	recurse(t_vhead *head)
{
	t_vlist *tmp;

	if (!head || !head->first)
		return;
	tmp = head->first;
	while (tmp)
	{
		get_folder_data(tmp->content);
		tmp = tmp->next;
	}
}

DIR 	*get_directory_pointer(char *path)
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

bool	get_folder_data(char *path)
{
	DIR 			*dir;
	struct dirent 	*dent;
	char			*folder;
	t_vhead			*head;

	head = NULL;
	if (!(dir = get_directory_pointer(path)))
		return (false);
	head = ft_vheadnew(2);
	while ((dent = readdir(dir)) != NULL)
	{
		if (dent->d_name[0] != '.' && (folder = get_file_data(path, dent->d_name)))
		{
			ft_vheadaddpoint(&head, folder, 2);
		}
	}
	write(1, "\n", 1);
	closedir(dir);
	recurse(head);
	return (true);
}