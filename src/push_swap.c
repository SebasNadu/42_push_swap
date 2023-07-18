/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:32 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/18 19:12:38 by sebasnadu        ###   ########.fr       */
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

size_t	find_pos(t_stack *stack, size_t size, size_t index)
{
	t_stack	*tmp;
	size_t	i;

	tmp = stack;
	i = 0;
	while (i < size)
	{
		if (tmp->o_index == index)
			return (i);
		tmp = tmp->next;
		++i;
	}
	return (0);
}

int	sorted_by(t_data *data, size_t is_a, size_t low)
{
	int		i;
	t_stack	*stack;

	if (is_a)
		stack = data->stack_a;
	else
		stack = data->stack_b;
	i = -1;
	if (is_a)
		while ((size_t)++i < data->a_size - low - 1
			&& stack->next->o_index == stack->o_index + 1)
			stack = stack->next;
	else
		while ((size_t)++i < data->b_size - low - 1
			&& stack->next->o_index == stack->o_index - 1)
			stack = stack->next;
	if ((size_t)i == data->a_size - low - 1 || (size_t)i == data->b_size - low - 1 || i == 0)
		return (1);
	return (0);
}

void	pushb_in_order(t_data *data, size_t index, size_t next)
{
	size_t	target_pos;

	target_pos = find_pos(data->stack_b, data->b_size, index);
	if (data->stack_b->o_index == next)
		operations_parser(data, "pa");
	if (target_pos >= data->b_size / 2)
	{
		while (data->stack_b->o_index != index)
		{
			operations_parser(data, "rb");
			if (data->stack_b->o_index == next)
				operations_parser(data, "pa");
		}
	}
	else
	{
		while (data->stack_b->o_index != index)
		{
			operations_parser(data, "rrb");
			if (data->stack_b->o_index == next)
				operations_parser(data, "pa");
		}
	}
}

void	pusha_in_order(t_data *data, size_t index, size_t next)
{
	size_t	target_pos;

	target_pos = find_pos(data->stack_a, data->a_size, index);
	if (data->stack_a->o_index == next)
		operations_parser(data, "pb");
	if (target_pos >= data->a_size / 2)
	{
		while (data->stack_a->o_index != index)
		{
			operations_parser(data, "ra");
			if (data->stack_a->o_index == next)
				operations_parser(data, "pb");
		}
	}
	else
	{
		while (data->stack_a->o_index != index)
		{
			operations_parser(data, "rra");
			if (data->stack_a->o_index == next)
				operations_parser(data, "pb");
		}
	}
}

size_t	swap_tops(t_data *d, t_stack *s_a, t_stack *s_b)
{
	size_t	moves;

	moves = 0;
	if ((d->a_size >= 2 && s_a->o_index > s_a->next->o_index)
		&& (d->b_size >= 2 && s_b->o_index < s_b->next->o_index))
		moves = operations_parser(d, "ss");
	else
	{
		if ((d->a_size >= 2 && s_a->o_index > s_a->next->o_index))
			moves = operations_parser(d, "sa");
		if ((d->b_size >= 2 && s_b->o_index < s_b->next->o_index))
			moves = operations_parser(d, "sb");
	}
	return (moves);
}

size_t	swap_bottoms(t_data *d, t_stack *s_a, t_stack *s_b)
{
	size_t	moves;

	moves = 0;
	if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index && s_a->o_index
		< s_a->next->o_index && d->b_size >= 2 && s_b->o_index
		< s_b->prev->o_index && s_a->o_index > s_a->next->o_index)
		moves += operations_parser(d, "rrr");
	else if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index
		&& d->b_size >= 2 && s_b->o_index < s_b->prev->o_index)
		moves += operations_parser(d, "rr");
	else
	{
		if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index
			&& s_a->o_index < s_a->next->o_index)
			moves += operations_parser(d, "rra");
		if (d->b_size >= 2 && s_b->o_index < s_b->prev->o_index
			&& s_a->o_index > s_a->next->o_index)
			moves += operations_parser(d, "rrb");
		if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index)
			moves += operations_parser(d, "ra");
		if (d->b_size >= 2 && s_b->o_index < s_b->prev->o_index)
			moves += operations_parser(d, "rb");
	}
	return (moves);
}

void	three_sort(t_data *data, size_t low, size_t high)
{
	size_t	moves;
	size_t	med;

	med = (low + (high - low)) / 2;
	while (1)
	{
		moves = 0;
		if ((data->stack_a->o_index <= med && data->stack_a->next->o_index
				<= med) || (data->stack_a->o_index > med
				&& data->stack_a->next->o_index > med))
			moves += swap_tops(data, data->stack_a, data->stack_b);
		moves += swap_bottoms(data, data->stack_a, data->stack_b);
		moves += swap_tops(data, data->stack_a, data->stack_b);
		if (data->a_size >= 3 && data->stack_a->prev->o_index
			== data->stack_a->o_index + 1)
			moves += operations_parser(data, "rra");
		if (data->b_size >= 3 && data->stack_b->prev->o_index
			== data->stack_b->o_index - 1)
			moves += operations_parser(data, "rrb");
		moves += swap_tops(data, data->stack_a, data->stack_b);
		if (!moves)
			break ;
	}
}

void	five_sort_a(t_data *data, size_t low, size_t high)
{
	int		i;

	if (data->a_size <= 3)
		return (three_sort(data, low, high));
	i = 0;
	while (!sorted_by(data, 1, 0) && i < 2)
	{
		three_sort(data, low, high);
		if (sorted_by(data, 1, 0))
			break ;
		operations_parser(data, "pb");
		++i;
	}
	while (i)
	{
		three_sort(data, low, high);
		operations_parser(data, "pa");
		--i;
	}
	three_sort(data, low, high);
}

void	insert_sort_b(t_data *data, size_t high, size_t low)
{
	size_t	index;
	size_t	pushes;

	pushes = 0;
	while (data->b_size && data->stack_a->o_index > low)
	{
		index = high - pushes;
		if (index <= low)
			pushb_in_order(data, index, data->f_s);
		else
			pushb_in_order(data, index, index - 1);
		operations_parser(data, "pa");
		++pushes;
		three_sort(data, low, high);
		if (data->stack_a->o_index == index - 1)
			++pushes;
	}
}

void	insert_sort_a(t_data *data, size_t low, size_t high)
{
	size_t	index;
	size_t	pushes;
	size_t	check_b;

	pushes = 0;
	check_b = 1;
	while (data->a_size > 5 && check_b
		&& !sorted_by(data, 1, data->a_size - 1 - high - low - pushes))
	{
		check_b = 0;
		index = low + pushes;
		if (index >= high)
			pusha_in_order(data, index, data->f_s);
		else
			pusha_in_order(data, index, index + 1);
		if (data->stack_a->o_index < high)
		{
			operations_parser(data, "pb");
			++pushes;
		}
		three_sort(data, low, high);
		if (data->stack_b->o_index == index + 1)
			++pushes;
		if (data->b_size > 0 && data->stack_b->o_index < high)
			check_b = 1;
	}
	if (data->a_size <= 5 && !sorted_by(data, 1, 0))
		five_sort_a(data, low + pushes, high);
	while (pushes--)
		operations_parser(data, "pa");
}

void	twin_insert_sort(t_data *data, size_t low, size_t high)
{
	size_t	med;

	med = (low + (high - low)) / 2;
	insert_sort_a(data, med + 1, low);
	insert_sort_b(data, med, low);
}

void	next_sort(t_data *data, size_t low, size_t high, size_t is_end)
{
	size_t	med;

	med = (low + (high - low)) / 2;
	if (high - low <= 31)
		twin_insert_sort(data, low, high);
	else
		quick_sort_a(data, med + 1, high, is_end);
	if (!is_end && data->b_size)
		quick_sort_b(data, low, med, is_end);
}

void	quick_sort_a(t_data *data, size_t low, size_t high, size_t is_end)
{
	size_t	to_sort;
	size_t	med;

	if (!is_end && high - low <= 63)
		return (last_sort_a(data, low, high));
	to_sort = (high - low) / 2 + 1;
	med = (low + (high - low)) / 2;
	while (data->a_size && to_sort)
	{
		if (data->stack_a->o_index <= med)
		{
			operations_parser(data, "pb");
			--to_sort;
			if (to_sort > 1 && data->b_size >= 2
				&& data->stack_b->o_index == med)
				operations_parser(data, "rb");
		}
		else
			operations_parser(data, "ra");
	}
	if (data->b_size > 1 && data->stack_b->prev->o_index == med)
		operations_parser(data, "rrb");
	while (data->a_size > 1 && data->stack_a->prev->o_index <= high
		&& high != data->f_s - 1)
		operations_parser(data, "rra");
	next_sort(data, low, high, is_end);
}

void	quick_sort_b(t_data *data, size_t high, size_t low, size_t is_end)
{
	size_t	to_sort;
	size_t	med;

	if (high - low <= 63)
		return (last_sort_b(data, high, low));
	med = low + (high - low) / 2;
	to_sort = high - med;
	while (data->b_size && to_sort)
	{
		if (data->stack_b->o_index > med)
		{
			operations_parser(data, "pa");
			--to_sort;
		}
		else
			operations_parser(data, "rb");
	}
	while (data->b_size > 1 && data->stack_b->prev->o_index >= low && low != 0)
		operations_parser(data, "rrb");
	next_sort(data, low, high, is_end);
}

void	last_sort_a(t_data *data, size_t low, size_t high)
{
	if (high - low <= 15)
		insert_sort_a(data, low, high);
	else
		quick_sort_a(data, low, high, 1);
	if (data->b_size && high - low > 31)
		quick_sort_b(data, low, high, 1);
}

void	last_sort_b(t_data *data, size_t low, size_t high)
{
	if (high - low <= 15)
		insert_sort_b(data, low, high);
	else
		quick_sort_b(data, low, high, 1);
	if (data->b_size && high - low > 31)
		quick_sort_b(data, low, high, 1);
}

void	quick_sort_init(t_data *data, size_t low, size_t high)
{
	size_t	med;
	size_t	s_med;
	size_t	to_sort;

	if (!check_if_sorted(data->stack_a, data->a_size) && high - low <= 63)
		return (last_sort_a(data, low, high));
	med = (low + (high - low)) / 2;
	s_med = (low + (med - low)) / 2;
	to_sort = (high - low) / 2 + 2;
	while (--to_sort && !sorted_by(data, 1, 0))
	{
		if (data->stack_a->o_index <= med)
		{
			operations_parser(data, "pb");
			if (data->b_size >= 2 && data->stack_b->next->o_index > s_med
				&& data->stack_b->o_index <= s_med)
				operations_parser(data, "sb");
		}
		else
			operations_parser(data, "ra");
	}
	if (sorted_by(data, 1, 0))
		return (insert_sort_b(data, data->stack_a->o_index - 1, low));
	quick_sort_a(data, med + 1, high, 0);
	quick_sort_b(data, med, s_med + 1, 0);
	quick_sort_b(data, s_med, low, 0);
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
		quick_sort_init(data, 0, data->a_size - 1);
		// binary_radix_sort(data, leftmost_bit(
		// 		find_highest(data->stack_a, data->a_size)));
}
