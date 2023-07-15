/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:57:53 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/15 15:58:11 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

size_t	find_highest(t_stack *stack, int size)
{
	size_t	highest;
	int		i;

	highest = stack->o_index;
	i = -1;
	while (++i < size)
	{
		if (stack->o_index > highest)
			highest = stack->o_index;
		stack = stack->next;
	}
	return (highest);
}

size_t	find_lowest(t_stack *stack, int size)
{
	size_t	lowest;
	int		i;

	lowest = stack->o_index;
	i = -1;
	while (++i < size)
	{
		if (stack->o_index < lowest)
			lowest = stack->o_index;
		stack = stack->next;
	}
	return (lowest);
}
