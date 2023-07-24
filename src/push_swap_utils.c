/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:57:53 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/24 11:13:48 by sebasnadu        ###   ########.fr       */
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
