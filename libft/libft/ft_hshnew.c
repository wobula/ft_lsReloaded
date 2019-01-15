/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hshnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rschramm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 15:18:32 by rschramm          #+#    #+#             */
/*   Updated: 2017/01/13 18:13:20 by rschramm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_hshnode *ft_hshnewnode(void)
{
	t_hshnode *new;

	new = (t_hshnode*)ft_memalloc(sizeof(t_hshnode));
	new->count = 0;
	new->first = NULL;
	new->last = NULL;
	return (new);
}

t_hsh	*ft_hshnew(size_t count, size_t size)
{
	t_hsh	*new_table;
	size_t	x;

	new_table = (t_hsh*)ft_memalloc(sizeof(t_hsh));
	new_table->data = (t_hshnode**)ft_memalloc(sizeof(t_hshnode*) * (count + 1));
	new_table->data[count] = 0;
	new_table->size = size;
	new_table->count = count;
	x = 0;
	do
	{
		new_table->data[x] = ft_hshnewnode();
	} while (++x < count);
	return (new_table);
}

size_t	ft_hash(size_t data, size_t count)
{
	ft_printf("Hash elements data: %zu, count: %zu,\n", data, count);
	size_t index = data % count;
	ft_printf("Index: %zu\n", index);
	return (index);
}

void	ft_hshadd(t_hsh *table, void *data)
{
	size_t index;

	ft_printf("%p\n", data);
	ft_printf("count: %zu\n", table->count);
	index = ft_hash((size_t)&data, table->count);
	ft_printf("Adding element at index %zu\n", index);
	if (table->data[index]->first == NULL)
	{
		ft_printf("Adding element to the first node\n");
		table->data[index]->first = ft_lstnew(data, sizeof(data));
		table->data[index]->last = table->data[index]->first;
	}
	else
	{
		ft_printf("Adding element to the next node node\n");
		table->data[index]->last->next = ft_lstnew(data, sizeof(data));
		table->data[index]->last->next->prev = table->data[index]->last;
		table->data[index]->last = table->data[index]->last->next;
	}
}

bool	ft_hshremove(t_hsh *table, void *data)
{
	size_t index;

	ft_printf("%p\n", data);
	ft_printf("count: %zu\n", table->count);
	index = ft_hash((size_t)&data, table->count);
	ft_printf("removing element at index %zu\n", index);
	/*if (table->data[index]->first == NULL)
	{
		ft_printf("Adding element to the first node\n");
		table->data[index]->first = ft_lstnew(data, sizeof(data));
		table->data[index]->last = table->data[index]->first;
	}
	else
	{
		ft_printf("Adding element to the next node node\n");
		table->data[index]->last->next = ft_lstnew(data, sizeof(data));
		table->data[index]->last->next->prev = table->data[index]->last;
		table->data[index]->last = table->data[index]->last->next;
	}*/
	return (true);
}

/*
	if (table->data[index]->first == NULL)
	{
		return (false);
	}
	tmp = table->data[index]->first;
	while (tmp)
	{
		if (tmp->content == data)
		{
			break;
		}
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		return (false);
	}
	if (table->data[index]->last == tmp)
	{
		table->data[index]->last = table->data[index]->last->prev;
	}
	if (tmp->prev)
		tmp->prev->next = tmp->next;
	if (tmp->next)
		tmp->next->prev = tmp->prev;
	free(tmp);
	return (true);
*/

void	ft_hshprint(t_hsh *table)
{
	size_t x;
	t_list *tmp;

	x = 0;
	do
	{
		if (table->data[x]->first == NULL)
			ft_printf("Index %zu: NULL\n", x);
		else
		{
			size_t z = 0;
			tmp = table->data[x]->first;
			while(tmp != NULL)
			{
				ft_printf("index: %zu, node: %zu, data: %s\n", x, z, tmp->content);
				z++;
				tmp = tmp->next;
			}
		}
	}
	while (++x < table->count);
	ft_printf("Hash Table Info:\n");
	ft_printf("Count: %zu\n", table->count);
	ft_printf("Data Size: %zu\n", table->size);
}