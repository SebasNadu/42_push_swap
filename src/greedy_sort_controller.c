/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy_sort_controller.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:36:20 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/09/18 15:49:12 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	is_bigger(int a, int b, int a_pos, int b_pos)
{
	if (a < 0)
		a = a * -1;
	if (b < 0)
		b = b * -1;
	if (a_pos < 0)
		a_pos = a_pos * -1;
	if (b_pos < 0)
		b_pos = b_pos * -1;
	if (a + b > a_pos + b_pos)
		return (1);
	return (0);
}

void	rotate_a(t_data *data, int a)
{
	while (a)
	{
		if (a > 0)
		{
			operations_parser(data, "ra");
			a--;
		}
		else
		{
			operations_parser(data, "rra");
			a++;
		}
	}
}

void	rotate_b(t_data *data, int b)
{
	while (b)
	{
		if (b > 0)
		{
			operations_parser(data, "rb");
			b--;
		}
		else
		{
			operations_parser(data, "rrb");
			b++;
		}
	}
}

void	rotate_same(t_data *data, int *a, int *b)
{
	while (*a && *b && (*a > 0 && *b > 0))
	{
		operations_parser(data, "rr");
		*a = *a - 1;
		*b = *b - 1;
	}
	while (*a && *b && (*a < 0 && *b < 0))
	{
		operations_parser(data, "rrr");
		*a = *a + 1;
		*b = *b + 1;
	}
}

void	get_min_rotate(t_data *data, int *a, int *b)
{
	t_stack	*tmp;
	int		a_pos;
	int		b_pos;
	int		index;
	int		num;

	index = 0;
	tmp = data->stack_b;
	while (index < (int)data->b_size)
	{
		num = tmp->o_index;
		a_pos = set_a_pos(num, data);
		if (index >= ((int)data->b_size + 1) / 2)
			b_pos = (data->b_size - index) * -1;
		else
			b_pos = index;
		if (index == 0 || is_bigger(*a, *b, a_pos, b_pos))
		{
			*a = a_pos;
			*b = b_pos;
		}
		tmp = tmp->next;
		index++;
	}
}
