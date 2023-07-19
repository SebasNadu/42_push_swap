/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 14:50:30 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/19 13:53:08 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	init_data(t_data *data)
{
	(*data).stack_a = NULL;
	(*data).stack_b = NULL;
	(*data).f_s = 0;
	(*data).prev_op = "   ";
	(*data).a_size = 0;
	(*data).b_size = 0;
}

static int	append_node(t_data *data, int nbr, int index)
{
	t_stack	*new;
	t_stack	*stack;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->data = nbr;
	new->next = NULL;
	new->prev = NULL;
	new->u_index = index;
	if (!(*data).stack_a)
		(*data).stack_a = new;
	else
	{
		stack = (*data).stack_a;
		while (stack->next)
			stack = stack->next;
		new->prev = stack;
		stack->next = new;
	}
	(*data).a_size += 1;
	return (1);
}

void	stack_filler(t_data *data, char **av, int is_a_dup)
{
	long	nbr;
	int		i;

	i = 0;
	while (av[i])
	{
		if (!check_if_int(av[i]))
			error_free(data, av, is_a_dup);
		nbr = ft_atol(av[i]);
		if (nbr < INT_MIN || nbr > INT_MAX)
			error_free(data, av, is_a_dup);
		if (check_if_dup(*data, (int)nbr))
			error_free(data, av, is_a_dup);
		if (!append_node(data, (int)nbr, i))
			error_free(data, av, is_a_dup);
		++i;
	}
	data->f_s = data->a_size;
}
