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

char	*make_path(char *path, char *file)
{
	char *new_path;

	new_path = ft_vhstrjoin(path, "/", 2);
	new_path = ft_vhstrjoin(path, file, 2);
	return (new_path);
}

bool	get_dir_contents(char *path)
{
	DIR 			*dir;
	struct dirent 	*dent;

	dir = opendir(path);
	if (dir != NULL)
	{
		while ((dent = readdir(dir)) != NULL)
		{
			get_data(path, dent->d_name);
		}
	}
	closedir(dir);
	return (true);
}

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

	ft_printf("--Starting LS\n\n");
	if (argv[1] != NULL)
	{
		ft_printf("lstat:\n");
		if (lstat(argv[1], &sb) == -1)
		{
			ft_printf("Invalid file: %s\n", argv[1]);
			return (-1);
		}
		if (S_ISDIR(sb.st_mode) == true)
		{
			ft_printf("Getting folder data\n");
			get_dir_contents(argv[1]);
		}
		else
		{
			ft_printf("Getting file data\n");
			get_data(".", argv[1]);
		}
	}
	return (0);
}