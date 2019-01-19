/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

bool	get_dir_contents(char *path);

char	*make_path(char *path, char *file)
{
	char *new_path;

	new_path = ft_vhstrjoin(path, "/", 2);
	new_path = ft_vhstrjoin(path, file, 2);
	return (new_path);
}

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

	if (head->first == NULL)
		return;
	tmp = head->first;
	while (tmp)
	{
		get_dir_contents(tmp->content);
		tmp = tmp->next;
	}
}

bool	get_dir_contents(char *path)
{
	DIR 			*dir;
	struct dirent 	*dent;
	char			*folder;
	t_vhead			*head;
	t_vlist			*lst;

	dir = opendir(path);
	ft_printf("%s: \n", path);
	if (dir != NULL)
	{
		head = ft_vheadnew(2);
		while ((dent = readdir(dir)) != NULL)
		{
			if ((folder = get_data(path, dent->d_name)) != NULL && dent->d_name[0] != '.')
			{
				lst = ft_vlstpoint(folder, 2);
				ft_vheadaddend(&head, lst);
			}
		}
	}
	write(1, "\n", 1);
	closedir(dir);
	recurse(head);
	return (true);
}

//1. get padding info
//2. print with padding info
//3. if recursive, repeat process for all folders

int 		main(int argc, char **argv)
{
	//t_args 		meta;

	/*if (preprocessor(&meta, argv, argc) == false)
	{
		return (1);
	}
	processor(&meta);
	//postprocessor(&meta);*/
	struct stat sb;

	ft_printf("--1 Starting LS\n\n");
	if (argv[1] != NULL)
	{
		ft_printf("--2 lstat:\n");
		if (lstat(argv[1], &sb) == -1)
		{
			ft_printf("--2.1 Invalid file: %s\n", argv[1]);
			return (-1);
		}
		if (S_ISDIR(sb.st_mode) == true)
		{
			ft_printf("--2.2 Getting folder data\n");
			get_dir_contents(argv[1]);
		}
		else
		{
			ft_printf("--2.3 Getting file data\n");
			get_data(".", argv[1]);
		}
	}
	return (0);
}