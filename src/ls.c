#include "../includes/ft_ls.h"


void 	preprocessor_constructor(t_args *meta, char **argv, int argc)
{
	meta->argv = argv;
	meta->argc = argc;
	ft_bzero(meta->buff, 127);
}

void	extract(t_args *meta, char *arg)
{
	int x;


	x = 0;
	while (arg[++x] != '\0')
	{
		meta->buff[arg[x]] = true;
	}
}

void 	extract_options(t_args *meta)
{
	int x;

	x = 0;
	while (++x < meta->argc)
	{
		if (meta->argv[x][0] == '-')
		{
			extract(meta, meta->argv[x]);
		}
	}
}

void	print_args(t_args *meta)
{
	int x = -1;

	ft_printf("options:");
	while (++x < 127)
	{
		if (meta->buff[x] == true)
		{
			ft_printf(" %c ", x);
		}
	}
}

bool 	preprocessor(t_args *meta, char **argv, int argc)
{
	preprocessor_constructor(meta, argv, argc);
	extract_options(meta);
	//validate options
	//extract_args
	print_args(meta);
	return true;
}

int 	main(int argc, char **argv)
{
	t_args meta;

	preprocessor(&meta, argv, argc);
	ft_printf("\nend");
	return (0);
}