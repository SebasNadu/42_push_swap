/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:18:57 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/13 15:35:06 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	swap(t_stack **stack)
{
	t_stack	*tmp;

	if (!(*stack) || !(*stack)->next)
		return ;
	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	tmp->prev = (*stack)->prev;
	(*stack)->prev = tmp;
	tmp->next->prev = (*stack);
	tmp->next = (*stack);
	tmp->prev->next = tmp;
	(*stack) = tmp;
}

void	rotate(t_stack **stack, int is_rev)
{
	if (!(*stack) || !(*stack)->prev || !(*stack)->next)
		return ;
	if (is_rev)
		*stack = (*stack)->prev;
	else
		*stack = (*stack)->next;
}

static void	ft_stackadd_front(t_stack **stack, t_stack *new_node)
{
	if (!new_node)
		return ;
	if (*stack == NULL)
	{
		new_node->next = NULL;
		new_node->prev = NULL;
		*stack = new_node;
	}
	else
	{
		new_node->next = *stack;
		new_node->prev = (*stack)->prev;
		(*stack)->prev->next = new_node;
		(*stack)->prev = new_node;
		*stack = new_node;
	}
}

void	push(t_stack **dest, t_stack **src, size_t *dest_size, size_t *src_size)
{
	t_stack	*node_to_push;

	if (*src == NULL)
		return ;
	node_to_push = *src;
	*src = (*src)->next;
	if (*src)
	{
		(*src)->prev = node_to_push->prev;
		node_to_push->prev->next = *src;
	}
	ft_stackadd_front(dest, node_to_push);
	*src_size -= 1;
	*dest_size += 1;
}
