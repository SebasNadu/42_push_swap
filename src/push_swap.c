/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:20:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/24 11:02:37 by sebasnadu        ###   ########.fr       */
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

int	find_ordered(t_stack *stack, size_t size, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (c == 'a' && i < (int)size)
	{
		if ((int)stack->o_index == i)
			++count;
		else
			count = 0;
		++i;
		stack = stack->next;
	}
	i = (int)size - 1;
	while (c == 'b' && i >= 0)
	{
		if ((int)stack->o_index == i)
			++count;
		else
			count = 0;
		--i;
		stack = stack->next;
	}
	return (count);
}

void	bit_sort(t_data *data, size_t bit_place)
{
	size_t	iter_length;
	size_t	limit;

	iter_length = data->a_size;
	limit = find_ordered(data->stack_a, data->a_size, 'a');
	while (0 < iter_length - limit
		&& !check_if_sorted(data->stack_a, data->a_size))
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
		--iter_length;
	}
	iter_length = data->b_size;
	limit = find_ordered(data->stack_b, data->b_size, 'b');
	while (0 < iter_length - limit)
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
	while (data->b_size)
		operations_parser(data, "pa");
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

void	push_swap(t_data *data)
{
	if (data->a_size == 2)
		operations_parser(data, "sa");
	else if (data->a_size == 3)
		sort_three(data);
	else if (data->a_size == 4)
		sort_four(data);
	else if (data->a_size == 5)
		sort_five(data);
	else
		binary_radix_sort(data, leftmost_bit(data->a_size - 1));
}
