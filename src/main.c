/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/13 15:04:13 by sebasnadu        ###   ########.fr       */
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

void	exit_free(t_data *data)
{
	free_stack(data->stack_a, data->a_size);
	free_stack(data->stack_b, data->b_size);
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
	merge_sort(&data.stack_a, data.a_size, merge);
	set_o_index(data.stack_a, data.a_size);
	set_doub_link(data.stack_a, data.a_size);
	merge_sort(&data.stack_a, data.a_size, merge_by_uindex);
	set_doub_link(data.stack_a, data.a_size);
	ft_stackiter(data.stack_a, data.a_size, (*ft_putnbr_fd));
	operators_parser(&data, "pb");
	ft_stackiter(data.stack_a, data.a_size, (*ft_putnbr_fd));
	ft_stackiter(data.stack_b, data.b_size, (*ft_putnbr_fd));
	exit_free(&data);
	return (0);
}
