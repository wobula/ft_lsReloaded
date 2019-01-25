/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preprocessor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/30 15:58:34 by rschramm          #+#    #+#             */
/*   Updated: 2017/02/11 12:51:04 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

static void	extract_opt(t_args *meta, char *arg)
{
	int x;

	x = 0;
	while (arg[++x] != '\0')
	{
		meta->opts[arg[x]] = true;
	}
}

static bool get_opts(t_args *meta)
{
	int x;

	x = 0;
	while (++x < meta->argc)
	{
		if (meta->argv[x][0] == '\0')
			return (false);
		if (meta->argv[x][0] == '-')
		{
			meta->opt_count++;
			extract_opt(meta, meta->argv[x]);
		}
	}
	return (true);
}

static bool	validate_opts(t_args *meta)
{
	int x;

	x = -1;
	while (++x < 127)
	{
		if (meta->opts[x] == true)
		{
			if ((OPT_CHECK(x)) == false)
			{
				INVALID_OPT(x);
				return (false);
			}
		}
	}
	return (true);
}

static bool	extract_args(t_args *meta)
{
	int x;
	int curr;

	x = 0;
	curr = 0;
	while (++x < meta->argc)
	{
		if (meta->argv[x][0] == '\0')
			return (false);
		if (meta->argv[x][0] != '-')
		{
			meta->args[curr] = meta->argv[x];
			curr++;
		}
	}
	return (true);
}

static bool	point_args(t_args *meta)
{
	meta->arg_count = meta->argc - meta->opt_count - 1;
	meta->args = (char**)ft_vhmemalloc(sizeof(char*) * (meta->arg_count + 1), 0);
	if (!meta->args)
		return (false);
	meta->args[meta->arg_count] = 0;
	return (true);
}

static bool	validate_args(t_args *meta)
{
	int 		x;
	struct stat sb;

	x = -1;
	while (++x < meta->arg_count)
	{
		if (lstat(meta->args[x], &sb) == -1)
		{
			INVALID_FILE(meta->args[x]);
			return (false);
		}
	}
	return (true);
}

static 	bool count_files_folders(t_args *meta)
{
	int 		x;
	struct stat sb;

	x = -1;
	while (++x < meta->arg_count)
	{
		lstat(meta->args[x], &sb);
		if (S_ISDIR(sb.st_mode) == true)
			meta->folders++;
		else
			meta->files++;
	}
	return (true);
}

typedef bool (*pre)(t_args *);

void		preprocessor_constructor(t_args *meta, pre ptr[], char **argv, int argc)
{
	meta->files = 0;
	meta->folders = 0;
	meta->argv = argv;
	meta->argc = argc;
	meta->arg_count = 0;
	meta->opt_count = 0;
	meta->sorted_files = NULL;
	meta->sorted_folders = NULL;
	ft_bzero(meta->opts, 127);
	ptr[0] = &get_opts;
	ptr[1] = &validate_opts;
	ptr[2] = &point_args;
	ptr[3] = &extract_args;
	ptr[4] = &validate_args;
	ptr[5] = &count_files_folders;
}

int 		preprocessor(t_args *meta, char **argv, int argc)
{
	pre 	function[6];
	int 	x;

	x = -1;
	preprocessor_constructor(meta, function, argv, argc);
	while (++x < 6)
	{
		if (function[x](meta) == false)
		{
			return (0);
		}
	}
	return (1);
}