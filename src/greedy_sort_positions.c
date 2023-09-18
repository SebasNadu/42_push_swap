/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort_positions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:24:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/09/18 15:49:05 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	set_over_pos(t_data *data)
{
	int		pos;
	int		index;
	int		tmp;
	t_stack	*stack_a;

	pos = 0;
	tmp = 0;
	stack_a = data->stack_a;
	index = find_lowest(stack_a, data->a_size);
	while (pos < (int)data->a_size)
	{
		tmp = stack_a->o_index;
		if (tmp == index)
			break ;
		pos++;
		stack_a = stack_a->next;
	}
	if (pos >= ((int)data->a_size + 1) / 2)
		pos = (data->a_size - pos) * -1;
	return (pos);
}

static int	set_under_pos(t_data *data)
{
	int		pos;
	int		index;
	t_stack	*stack_a;

	pos = 0;
	stack_a = data->stack_a;
	index = find_highest(stack_a, data->a_size);
	while (pos < (int)data->a_size)
	{
		if ((int)stack_a->o_index == index)
			break ;
		pos++;
		stack_a = stack_a->next;
	}
	pos++;
	if (pos >= ((int)data->a_size + 1) / 2)
		pos = (data->a_size - pos) * -1;
	return (pos);
}

static int	set_mid_pos(int num, t_data *data)
{
	t_stack	*stack_a;
	int		pos;

	stack_a = data->stack_a;
	pos = 1;
	while (pos < (int)data->a_size)
	{
		if (num > (int)stack_a->o_index && num < (int)stack_a->next->o_index)
			break ;
		pos++;
		stack_a = stack_a->next;
	}
	if (pos >= ((int)data->a_size + 1) / 2)
		pos = (data->a_size - pos) * -1;
	return (pos);
}

int	set_a_pos(int num, t_data *data)
{
	int	pos;

	if (num < (int)find_lowest(data->stack_a, data->a_size))
		pos = set_over_pos(data);
	else if (num > (int)find_highest(data->stack_a, data->a_size))
		pos = set_under_pos(data);
	else
		pos = set_mid_pos(num, data);
	return (pos);
}
