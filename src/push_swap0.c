/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap0.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:20:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/19 12:21:10 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	sort_three(t_data *data)
{
	size_t	highest;

	highest = find_highest(data->stack_a, data->a_size);
	if (data->stack_a->o_index == highest)
		operations_parser(data, "ra");
	else if (data->stack_a->next->o_index == highest)
		operations_parser(data, "rra");
	if (data->stack_a->o_index > data->stack_a->next->o_index)
		operations_parser(data, "sa");
}

void	sort_four(t_data *data)
{
	size_t	lowest;

	lowest = find_lowest(data->stack_a, data->a_size);
	if (data->stack_a->prev->o_index == lowest)
		operations_parser(data, "rra");
	while (data->stack_a->o_index != lowest)
		operations_parser(data, "ra");
	operations_parser(data, "pb");
	sort_three(data);
	operations_parser(data, "pa");
}

void	sort_five(t_data *data)
{
	size_t	lowest;

	lowest = find_lowest(data->stack_a, data->a_size);
	if (data->stack_a->prev->o_index == lowest)
		operations_parser(data, "rra");
	if (data->stack_a->prev->prev->o_index == lowest)
	{
		operations_parser(data, "rra");
		operations_parser(data, "rra");
	}
	while (data->stack_a->o_index != lowest)
		operations_parser(data, "ra");
	operations_parser(data, "pb");
	sort_four(data);
	operations_parser(data, "pa");
}

void	bit_sort(t_data *data, size_t bit_place)
{
	size_t	iter_length;

	iter_length = data->a_size;
	while (0 < iter_length)
	{
		if ((data->stack_a->o_index >> bit_place) & 1)
			operations_parser(data, "ra");
		else
			operations_parser(data, "pb");
		--iter_length;
	}
	iter_length = data->b_size;
	while (0 < iter_length)
	{
		operations_parser(data, "pa");
		--iter_length;
	}
}

void	binary_radix_sort(t_data *data, size_t iter_length)
{
	size_t	i;

	i = 0;
	while (i < iter_length)
	{
		if (check_if_sorted(data->stack_a, data->a_size))
			break ;
		bit_sort(data, i);
		++i;
	}
}

size_t	leftmost_bit(size_t nbr)
{
	size_t	i;

	i = 0;
	while (nbr)
	{
		nbr >>= 1;
		++i;
	}
	return (i);
}
