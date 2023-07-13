/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_parsers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 15:33:43 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/13 15:34:47 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

static void	swap_parser(t_data *data, char *msg)
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

static void	rotate_parser(t_data *data, char *msg)
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

static void	push_parser(t_data *data, char *msg)
{
	if (ft_strncmp(msg, "pa", 2) == 0)
		push(&(*data).stack_a, &(*data).stack_b,
			&(*data).a_size, &(*data).b_size);
	if (ft_strncmp(msg, "pb", 2) == 0)
		push(&(*data).stack_b, &(*data).stack_a,
			&(*data).b_size, &(*data).a_size);
}

void	operations_parser(t_data *data, char *msg)
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
