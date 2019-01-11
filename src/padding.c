/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: giacomo <giacomo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/13 12:19:48 by giacomo           #+#    #+#             */
/*   Updated: 2017/12/13 12:25:51 by giacomo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

/*void	get_max_file_size_length(t_max_pad *maxi, long long number)
{
	int digit_count = 0;
	while (number > 0)
	{
		number = number / 10;
		digit_count++;
	}
	if (digit_count > maxi->file_size_length)
	{
		this->file_size_pad = maxi->digit_count;
	}
}

t_file_pad *pad_factory(void)
{
	t_file_pad *tmp;

	tmp = ft_vhmalloc(sizeof(t_file_pad), 2);
	tmp->user_pad = 0;
	tmp->group_pad = 0;
	tmp->file_size_pad = 0;
	tmp->digit_count = 0;
}

void	get_padding_info_file(t_vec *file, t_max_pad *maxi)
{
	file->info->this = pad_factory();
	file->info->this->file_size_pad = get_file_size_pad(maxi, file->info->size);

}

void	pad_constructor(t_max_pad *maxi)
{
	maxi->max_user_pad = 0;
	maxi->max_group_pad = 0;
	maxi->max_file_size_pad = 0;
	maxi->digit_count = 0;
}

void	get_padding_info(t_vec **files)
{
	t_max_pad maxi;
	int x;

	pad_constructor(&maxi);
	x = -1;
	while (files[x] != 0)
	{
		get_padding_info_file(files[x], &maxi);
	}
}*/

/*

if ((info->z = ft_strlen(files[info->x]->info->user)) > info->max_user_length)
		{
			info->max_user_length = info->z;
		}
		if ((info->z = ft_strlen(files[info->x]->info->group)) > info->max_group_length)
		{
			info->max_group_length = info->z;
		}
		get_max_file_size_length(info, files[info->x]->info->size);

*/
