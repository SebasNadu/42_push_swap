/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 18:54:32 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/09/18 15:51:47 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	three_div_instruct(t_data *data, size_t pivot1, size_t pivot2)
{
	if (data->b_size > 1 && data->stack_a->o_index
		> data->stack_a->next->o_index && data->stack_b->o_index
		< data->stack_b->next->o_index)
		operations_parser(data, "ss");
	if (data->stack_a->o_index < pivot1)
	{
		operations_parser(data, "pb");
		if (data->stack_a->o_index >= pivot2)
			operations_parser(data, "rr");
		else
			operations_parser(data, "rb");
	}
	else if (data->stack_a->o_index < pivot2)
		operations_parser(data, "pb");
	else
		operations_parser(data, "ra");
	if (data->b_size > 1 && data->stack_a->o_index
		> data->stack_a->next->o_index && data->stack_b->o_index
		< data->stack_b->next->o_index)
		operations_parser(data, "ss");
}

void	push_last_div(t_data *data)
{
	while (data->a_size > 5)
	{
		if (data->stack_b->o_index < data->stack_b->next->o_index
			&& data->stack_a->o_index > data->stack_a->next->o_index)
			operations_parser(data, "ss");
		operations_parser(data, "pb");
	}
	if (data->a_size == 2)
	{
		if (data->stack_a->o_index > data->stack_a->next->o_index)
			operations_parser(data, "sa");
	}
	else if (data->a_size == 3)
		sort_three(data);
	else if (data->a_size == 4)
		sort_four(data);
	else if (data->a_size == 5)
		sort_five(data);
}

void	push_three_division(t_data *data)
{
	int		index;
	size_t	pivot1;
	size_t	pivot2;

	pivot1 = data->a_size / 3;
	pivot2 = data->a_size * 2 / 3;
	index = data->a_size;
	while (index)
	{
		three_div_instruct(data, pivot1, pivot2);
		index--;
	}
	push_last_div(data);
}

void	sort_last(t_data *data)
{
	int	min_pos;

	min_pos = set_over_pos(data);
	while (min_pos)
	{
		if (min_pos > 0)
		{
			operations_parser(data, "ra");
			min_pos--;
		}
		else
		{
			operations_parser(data, "rra");
			min_pos++;
		}
	}
}

void	greedy_sort(t_data *data)
{
	int	a;
	int	b;

	push_three_division(data);
	while (data->b_size)
	{
		a = 0;
		b = 0;
		get_min_rotate(data, &a, &b);
		rotate_same(data, &a, &b);
		rotate_a(data, a);
		rotate_b(data, b);
		operations_parser(data, "pa");
	}
	sort_last(data);
}
