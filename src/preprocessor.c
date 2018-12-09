#include "../includes/ft_ls.h"

static void 	preprocessor_constructor(t_args *meta, char **argv, int argc)
{
	meta->argv = argv;
	meta->argc = argc;
	meta->opt_count = 0;
	meta->arg_count = 0;
	ft_bzero(meta->opts, 127);
}

static void		extract_opt(t_args *meta, char *arg)
{
	int x;


	x = 0;
	while (arg[++x] != '\0')
	{
		meta->opts[arg[x]] = true;
	}
}

static void 	handler_options(t_args *meta)
{
	int x;

	x = 0;
	while (++x < meta->argc)
	{
		if (meta->argv[x][0] == '-')
		{
			meta->opt_count++;
			extract_opt(meta, meta->argv[x]);
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

static void		print_opts(t_args *meta)
{
	int x = -1;

	ft_printf("options:");
	while (++x < 127)
	{
		if (meta->opts[x] == true)
		{
			ft_printf(" %c ", x);
		}
	}
	ft_printf("\n");
}

static void		extract_args(t_args *meta)
{
	int x;
	int curr;

	x = 0;
	curr = 0;
	while (++x < meta->argc)
	{
		if (meta->argv[x][0] != '-')
		{
			meta->args[curr] = meta->argv[x];
			curr++;
		}
	}
}

static void		handler_args(t_args *meta)
{
	meta->arg_count = meta->argc - meta->opt_count - 1;
	meta->args = (char**)ft_memalloc(sizeof(char*) * meta->arg_count + 1);
	meta->args[meta->arg_count] = 0;
	extract_args(meta);	
}

static void		print_args(t_args *meta)
{
	int x;

	ft_printf("Args:\n");
	x = -1;
	while (++x != meta->arg_count)
	{
		ft_printf("%d) %s\n", x, meta->args[x]);
	}
}

bool 			preprocessor(t_args *meta, char **argv, int argc)
{
	preprocessor_constructor(meta, argv, argc);
	handler_options(meta);
	if (!validate_opts(meta))
		return (false);
	handler_args(meta);
	//print_opts(meta);
	//print_args(meta);
	return (true);
}