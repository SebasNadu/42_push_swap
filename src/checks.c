/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:24:02 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/18 18:11:33 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int	check_if_sorted(t_stack *stack, int size)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	while (i < size -1)
	{
		if (tmp->data > tmp->next->data)
			return (0);
		tmp = tmp->next;
		++i;
	}
	return (1);
}

int	check_if_int(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		++i;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

int	check_if_dup(t_data data, int nbr)
{
	t_stack	*stack;

	if (data.a_size == 0)
		return (0);
	stack = data.stack_a;
	while (stack->next)
	{
		if (stack->data == nbr)
			return (1);
		stack = stack->next;
	}
	if (stack->data == nbr)
		return (1);
	return (0);
}
