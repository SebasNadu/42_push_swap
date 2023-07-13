/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 11:18:57 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/13 15:21:32 by sebasnadu        ###   ########.fr       */
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

void	swap_parser(t_data *data, char *msg)
{
	if (ft_strncmp(msg, "sa", 2) == 0)
	{
		if ((*data).a_size > 1)
			swap(&(*data).stack_a);
	}
	else if (ft_strncmp(msg, "sb", 2) == 0)
	{
		if ((*data).b_size > 1)
			swap(&(*data).stack_b);
	}
	else if (ft_strncmp(msg, "ss", 2) == 0)
	{
		if ((*data).a_size > 1 && (*data).b_size > 1)
		{
			swap(&(*data).stack_a);
			swap(&(*data).stack_b);
		}
	}
}

void	rotate_parser(t_data *data, char *msg)
{
	if (ft_strncmp(msg, "ra", 3) == 0 || ft_strncmp(msg, "rra", 3) == 0)
	{
		if ((*data).a_size > 1)
			rotate(&(*data).stack_a, ft_strlen(msg) == 3);
	}
	else if (ft_strncmp(msg, "rb", 3) == 0 || ft_strncmp(msg, "rrb", 3) == 0)
	{
		if ((*data).b_size > 1)
			rotate(&(*data).stack_b, ft_strlen(msg) == 3);
	}
	else if (ft_strncmp(msg, "rr", 3) == 0 || ft_strncmp(msg, "rrr", 3) == 0)
	{
		if ((*data).a_size > 1 && (*data).b_size > 1)
		{
			rotate(&(*data).stack_a, ft_strlen(msg) == 3);
			rotate(&(*data).stack_b, ft_strlen(msg) == 3);
		}
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
	if (*dest == NULL)
	{
		node_to_push->next = NULL;
		node_to_push->prev = NULL;
		*dest = node_to_push;
	}
	else
	{
		node_to_push->next = *dest;
		node_to_push->prev = (*dest)->prev;
		(*dest)->prev->next = node_to_push;
		(*dest)->prev = node_to_push;
		*dest = node_to_push;
	}
	*src_size -= 1;
	*dest_size += 1;
}

void	push_parser(t_data *data, char *msg)
{
	if (ft_strncmp(msg, "pa", 2) == 0)
		push(&(*data).stack_a, &(*data).stack_b,
			&(*data).a_size, &(*data).b_size);
	if (ft_strncmp(msg, "pb", 2) == 0)
		push(&(*data).stack_b, &(*data).stack_a,
			&(*data).b_size, &(*data).a_size);
}

void	operators_parser(t_data *data, char *msg)
{
	if (ft_strncmp(msg, "sa", 2) == 0 || ft_strncmp(msg, "sb", 2) == 0
		|| ft_strncmp(msg, "ss", 2) == 0)
		swap_parser(data, msg);
	else if (ft_strncmp(msg, "rra", 3) == 0 || ft_strncmp(msg, "rrb", 3) == 0
		|| ft_strncmp(msg, "rrr", 3) == 0 || ft_strncmp(msg, "ra", 2) == 0
		|| ft_strncmp(msg, "rb", 2) == 0 || ft_strncmp(msg, "rr", 2) == 0)
		rotate_parser(data, msg);
	else if (ft_strncmp(msg, "pa", 2) == 0 || ft_strncmp(msg, "pb", 2) == 0)
		push_parser(data, msg);
	ft_putstr_fd(msg, 1);
	write(1, "\n", 1);
}
