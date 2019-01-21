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

/*
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
}*/

/*t_vhead		*print_directory_contents(t_args *meta, t_vhead *head, char *path)
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
		print_selector(path, tmp->content)) != NULL)
		{
			ft_vheadaddpoint(&recursion, folder, 2);
		}
		tmp = tmp->next;
	}
	return (recursion);
}*/

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
	if (head->first == NULL)
		ft_printf("No first\n");
	return (head);
}

char	*construct_path(char *path, char *file)
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
		print_selector(meta, full_path, tmp->content);
		path = NULL;
		tmp = tmp->next;
	}
}

void		get_folder_data(t_args *meta, char *path)
{
	DIR 			*dir;
	t_vhead			*head;

	head = NULL;
	ft_printf("%s:\n", path);
	if (!(dir = get_directory_pointer(path)))
		return;
	if ((head = build_directory_structure(dir, path))->first == NULL)
		return;
	ft_sortbubblechar(&head);
	print_folder_contents(meta, head, path);
/*
	recursion = print_directory_contents(head, path);
	write(1, "\n", 1);
	closedir(dir);*/
	//recurse(recursion);
	return;
}