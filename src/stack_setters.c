/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_setters.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 15:52:02 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/15 15:52:25 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	set_o_index(t_stack *stack, int size)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	while (i < size)
	{
		tmp->o_index = i;
		tmp = tmp->next;
		++i;
	}
}

void	set_doub_circular_link(t_stack **stack, int size)
{
	t_stack	*current;
	t_stack	*next_node;
	int		i;

	i = 0;
	current = *stack;
	next_node = (*stack)->next;
	while (next_node != *stack && i < size - 1)
	{
		next_node->prev = current;
		current->next = next_node;
		current = next_node;
		next_node = next_node->next;
		++i;
	}
	current->next = *stack;
	(*stack)->prev = current;
}

void	set_doub_link(t_stack **stack, int size)
{
	t_stack	*current;
	t_stack	*next_node;
	int		i;

	i = 0;
	current = *stack;
	next_node = (*stack)->next;
	while (next_node != *stack && i < size - 1)
	{
		next_node->prev = current;
		current->next = next_node;
		current = next_node;
		next_node = next_node->next;
		++i;
	}
	current->next = NULL;
	(*stack)->prev = NULL;
}
