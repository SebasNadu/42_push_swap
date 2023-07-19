/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:32 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/19 14:47:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

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
	if ((size_t)i == data->a_size - 1
		|| (data->b_size - 1) - low == 0)
		return (1);
	return (0);
}

void	search_target_b(t_data *data, size_t index, size_t next)
{
	size_t	target_pos;

	target_pos = find_pos(data->stack_b, data->b_size, index);
	if (data->stack_b->o_index == next)
		psh(data, "pa");
	if (target_pos >= data->b_size / 2)
	{
		while (data->stack_b->o_index != index)
		{
			rot(data, "rb", 0);
			if (data->stack_b->o_index == next)
				psh(data, "pa");
		}
	}
	else
	{
		while (data->stack_b->o_index != index)
		{
			rrot(data, "rrb", 0);
			if (data->stack_b->o_index == next)
				psh(data, "pa");
		}
	}
}

void	search_target_a(t_data *data, size_t index, size_t next)
{
	size_t	target_pos;

	target_pos = find_pos(data->stack_a, data->a_size, index);
	if (data->stack_a->o_index == next)
		psh(data, "pb");
	if (target_pos >= data->a_size / 2)
	{
		while (data->stack_a->o_index != index)
		{
			rot(data, "ra", 0);
			if (data->stack_a->o_index == next)
				psh(data, "pb");
		}
	}
	else
	{
		while (data->stack_a->o_index != index)
		{
			rrot(data, "rra", 0);
			if (data->stack_a->o_index == next)
				psh(data, "pb");
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
			moves = swp(d, "sa", 1);
		if ((d->b_size >= 2 && s_b->o_index < s_b->next->o_index))
			moves = swp(d, "sb", 1);
	}
	return (moves);
}

size_t	swap_bottoms(t_data *d, t_stack *s_a, t_stack *s_b)
{
	size_t	moves;

	moves = 0;
	if ((d->a_size >= 2 && s_a->o_index > s_a->prev->o_index && s_a->o_index
			< s_a->next->o_index) && (d->b_size >= 2 && s_b->o_index
			< s_b->prev->o_index && s_a->o_index > s_a->next->o_index))
		moves += operations_parser(d, "rrr");
	else if ((d->a_size >= 2 && s_a->o_index > s_a->prev->o_index)
		&& (d->b_size >= 2 && s_b->o_index < s_b->prev->o_index))
		moves += operations_parser(d, "rr");
	else
	{
		if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index
			&& s_a->o_index < s_a->next->o_index)
			moves += rrot(d, "rra", 1);
		if (d->b_size >= 2 && s_b->o_index < s_b->prev->o_index
			&& s_a->o_index > s_a->next->o_index)
			moves += rrot(d, "rrb", 1);
		if (d->a_size >= 2 && s_a->o_index > s_a->prev->o_index)
			moves += rot(d, "ra", 1);
		if (d->b_size >= 2 && s_b->o_index < s_b->prev->o_index)
			moves += rot(d, "rb", 1);
	}
	return (moves);
}

void	three_sort(t_data *data, size_t low, size_t high)
{
	size_t	moves;
	size_t	med;

	med = low + ((high - low) / 2);
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
			moves += rrot(data, "rra", 1);
		if (data->b_size >= 3 && data->stack_b->prev->o_index
			== data->stack_b->o_index - 1)
			moves += rrot(data, "rrb", 1);
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
		psh(data, "pb");
		++i;
	}
	while (i)
	{
		three_sort(data, low, high);
		psh(data, "pa");
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
			search_target_b(data, index, data->f_s);
		else
			search_target_b(data, index, index - 1);
		psh(data, "pa");
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

	pushes = 0;
	while (data->a_size > 5 && (data->b_size == 0 || data->stack_b->o_index < high)
		&& !sorted_by(data, 1, data->a_size - 1 - high - low - pushes))
	{
		index = low + pushes;
		if (index >= high)
			search_target_a(data, index, data->f_s);
		else
			search_target_a(data, index, index + 1);
		if (data->stack_a->o_index < high)
		{
			psh(data, "pb");
			++pushes;
		}
		three_sort(data, low, high);
		if (data->stack_b->o_index == index + 1)
			++pushes;
	}
	if (data->a_size <= 5 && !sorted_by(data, 1, data->a_size))
	{
		five_sort_a(data, low + pushes, high);
	}
	while (pushes--)
		psh(data, "pa");
}

void	twin_insert_sort(t_data *data, size_t low, size_t high)
{
	size_t	med;

	med = low + ((high - low) / 2);
	insert_sort_a(data, med + 1, low);
	insert_sort_b(data, med, low);
}

void	next_sort(t_data *data, size_t low, size_t high, size_t is_end)
{
	size_t	med;

	med = low + ((high - low) / 2);
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
	med = low + ((high - low) / 2);
	while (data->a_size && to_sort)
	{
		if (data->stack_a->o_index <= med)
		{
			psh(data, "pb");
			--to_sort;
			if (to_sort > 1 && data->b_size >= 2
				&& data->stack_b->o_index == med)
				rot(data, "rb", 0);
		}
		else
			rot(data, "ra", 0);
	}
	if (data->b_size > 1 && data->stack_b->prev->o_index == med)
		rrot(data, "rrb", 0);
	while (data->a_size > 1 && data->stack_a->prev->o_index <= high
		&& high != data->f_s - 1)
		rrot(data, "rra", 0);
	next_sort(data, low, high, is_end);
}

void	quick_sort_b(t_data *data, size_t high, size_t low, size_t is_end)
{
	size_t	to_sort;
	size_t	med;

	if (high - low <= 63 && !is_end)
		return (last_sort_b(data, high, low));
	med = low + ((high - low) / 2);
	to_sort = high - med;
	while (data->b_size && to_sort)
	{
		if (data->stack_b->o_index > med)
		{
			psh(data, "pa");
			--to_sort;
		}
		else
			rot(data, "rb", 0);
	}
	while (data->b_size > 1 && data->stack_b->prev->o_index >= low && low != 0)
		rrot(data, "rrb", 0);
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
	med = low + ((high - low) / 2);
	s_med = low + ((med - low) / 2);
	to_sort = (high - low) / 2 + 1;
	while (to_sort && !sorted_by(data, 1, 0))
	{
		if (data->stack_a->o_index <= med)
		{
			psh(data, "pb");
			if (data->b_size >= 2 && data->stack_b->next->o_index > s_med
				&& data->stack_b->o_index <= s_med)
				rot(data, "rb", 0);
			--to_sort;
		}
		else
			rot(data, "ra", 0);
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
