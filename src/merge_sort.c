/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:11:01 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/15 15:42:55 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static t_stack	*get_node(t_stack *stack, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		stack = stack->next;
		++i;
	}
	return (stack);
}

t_stack	*merge_by_uindex(t_stack *left, t_stack *right)
{
	t_stack	*result;

	if (!left)
		return (right);
	if (!right)
		return (left);
	if (left->u_index <= right->u_index)
	{
		result = left;
		result->next = merge_by_uindex(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge_by_uindex(left, right->next);
	}
	return (result);
}

t_stack	*merge(t_stack *left, t_stack *right)
{
	t_stack	*result;

	if (!left)
		return (right);
	if (!right)
		return (left);
	if (left->data <= right->data)
	{
		result = left;
		result->next = merge(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge(left, right->next);
	}
	return (result);
}

void	merge_sort(t_stack **stack, int size,
		t_stack *(*f_merge)(t_stack *, t_stack *))
{
	t_stack	*left;
	t_stack	*right;

	if (size <= 1)
		return ;
	left = *stack;
	right = get_node(*stack, size / 2);
	left->prev = NULL;
	right->prev->next = NULL;
	right->prev = NULL;
	merge_sort(&left, size / 2, f_merge);
	merge_sort(&right, size - (size / 2), f_merge);
	*stack = f_merge(left, right);
	(*stack)->prev = NULL;
}
