/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radix_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 11:17:47 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/24 11:36:53 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	bit_sort(t_data *data, size_t bit_place)
{
	size_t	size;
	size_t	lmt;

	size = data->a_size;
	lmt = find_ordered(data->stack_a, data->a_size, 'a');
	while (0 < size-- - lmt && !check_if_sorted(data->stack_a, data->a_size))
	{
		if ((data->stack_a->o_index >> bit_place) & 1)
		{
			if (data->b_size > 1 && data->stack_b->o_index
				< data->stack_b->prev->o_index)
				operations_parser(data, "rr");
			else
				operations_parser(data, "ra");
		}
		else
			operations_parser(data, "pb");
	}
	size = data->b_size;
	lmt = find_ordered(data->stack_b, data->b_size, 'b');
	while (0 < size-- - lmt)
		operations_parser(data, "pa");
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
	while (data->b_size)
		operations_parser(data, "pa");
}
