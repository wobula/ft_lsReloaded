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

static void		extract_opt(t_args *meta, char *arg)
{
	int x;


	x = 0;
	while (arg[++x] != '\0')
	{
		meta->opts[arg[x]] = true;
	}
}

static void 	handler_options(t_args *meta, char **argv, int argc)
{
	int x;

	x = 0;
	while (++x < argc)
	{
		if (argv[x][0] == '-')
		{
			meta->opt_count++;
			extract_opt(meta, argv[x]);
		}
	}
}

static bool		validate_opts(t_args *meta)
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

static void		extract_args(t_args *meta, char **argv, int argc)
{
	int x;
	int curr;

	x = 0;
	curr = 0;
	while (++x < argc)
	{
		if (argv[x][0] != '-')
		{
			meta->args[curr] = argv[x];
			curr++;
		}
	}
}

static void		handler_args(t_args *meta, int argc)
{
	meta->arg_count = argc - meta->opt_count - 1;
	meta->args = (char**)ft_vhmalloc(sizeof(char*) * (meta->arg_count + 1), 0);
	meta->args[meta->arg_count] = 0;
}

static void 	preprocessor_constructor(t_args *meta, char **argv, int argc)
{
	meta->arg_count = 0;
	meta->args = NULL;
	meta->opt_count = 0;
	meta->sorted_files = NULL;
	meta->sorted_folders = NULL;
	ft_bzero(meta->opts, 127);
}

static bool		validate_args(t_args *meta)
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

bool 			preprocessor(t_args *meta, char **argv, int argc)
{
	preprocessor_constructor(meta, argv, argc);
	handler_options(meta, argv, argc);
	if (!validate_opts(meta))
		return (false);
	handler_args(meta, argc);
	extract_args(meta, argv, argc);
	if (!validate_args(meta))
		return (false);
	return (true);
}