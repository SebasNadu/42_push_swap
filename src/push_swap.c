/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:20:55 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/09/18 15:52:14 by sebasnadu        ###   ########.fr       */
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
		greedy_sort(data);
}
