/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/08 00:41:11 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// next step merge sort

void	init_data(t_data *data)
{
	(*data).stack_a = NULL;
	(*data).stack_b = NULL;
	(*data).a_size = 0;
	(*data).b_size = 0;
}

int	append_node(t_data *data, int nbr, int index)
{
	t_stack	*new;
	t_stack	*stack;

	new = malloc(sizeof(t_stack));
	if (!new)
		return (0);
	new->data = nbr;
	new->next = NULL;
	new->u_index = index;
	if (!(*data).stack_a)
		(*data).stack_a = new;
	else
	{
		stack = (*data).stack_a;
		while (stack->next)
			stack = stack->next;
		stack->next = new;
	}
	++(*data).a_size;
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
		if (check_if_rep(*data, (int)nbr))
			error_free(data, av, is_a_dup);
		if (!append_node(data, (int)nbr, i))
			error_free(data, av, is_a_dup);
		++i;
	}
}

void	ft_stackiter(t_stack *stack, void (*f)(int, int))
{
	if (!stack || !f)
		return ;
	while (stack)
	{
		f(stack->data, 1);
		stack = stack->next;
	}
}

void	exit_free(t_data *data)
{
	free_stack(data->stack_a);
	free_stack(data->stack_b);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 2 || (ac == 2 && !av[1][0]))
		return (1);
	else if (ac == 2)
		av = ft_split_argv(av[1], ' ');
	init_data(&data);
	stack_filler(&data, av + 1, ac == 2);
	if (ac == 2)
		free_vdup(av);
	ft_stackiter(data.stack_a, (*ft_putnbr_fd));
	exit_free(&data);
	return (0);
}
