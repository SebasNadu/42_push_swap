/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/10/12 16:54:37 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	ft_stackiter(t_stack *stack, int size, void (*f)(int, int))
{
	int	i;

	if (!stack || !f)
		return ;
	i = 0;
	while (i < size)
	{
		write(1, "\noindex: ", 8);
		f(stack->o_index, 1);
		write(1, " uindex: ", 8);
		f(stack->u_index, 1);
		write(1, " nbr: ", 6);
		f(stack->data, 1);
		stack = stack->next;
		++i;
	}
}

void	ft_stackiter_rev(t_stack *stack, int size, void (*f)(int, int))
{
	int	i;

	if (!stack || !f)
		return ;
	i = 0;
	stack = stack->prev;
	while (i < size)
	{
		write(1, "\noindex: ", 8);
		f(stack->o_index, 1);
		write(1, " uindex: ", 8);
		f(stack->u_index, 1);
		write(1, " nbr: ", 6);
		f(stack->data, 1);
		stack = stack->prev;
		++i;
	}
}

void	exit_free(t_data *data)
{
	free_stack(data->stack_a, data->a_size);
	free_stack(data->stack_b, data->b_size);
}

int	main(int ac, char **argv)
{
	t_data	data;
	char	**av;

	av = argv;
	if (ac < 2 || (ac == 2 && !av[1][0]))
		return (0);
	else if (ac == 2)
		av = ft_split_argv(av[1], ' ');
	init_data(&data);
	stack_filler(&data, av, ac == 2);
	if (ac == 2)
		free_vdup(av);
	if (!check_if_sorted(data.stack_a, data.a_size))
	{
		merge_sort(&data.stack_a, data.a_size, merge);
		set_o_index(data.stack_a, data.a_size);
		set_doub_link(&data.stack_a, data.a_size);
		merge_sort(&data.stack_a, data.a_size, merge_by_uindex);
		set_doub_circular_link(&data.stack_a, data.a_size);
		push_swap(&data);
	}
	exit_free(&data);
	return (0);
}
