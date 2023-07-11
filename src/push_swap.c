/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/11 14:50:48 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_stack	*get_node(t_stack *stack, int index)
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

void	merge_sort(t_stack **stack, int size)
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
	merge_sort(&left, size / 2);
	merge_sort(&right, size - (size / 2));
	*stack = merge(left, right);
	(*stack)->prev = NULL;
}

void	set_o_index(t_stack *stack)
{
	int		i;

	i = 0;
	while (stack)
	{
		stack->o_index = i;
		stack = (stack)->next;
		++i;
	}
}

// next step sort by u_index
void	sort_by_uindex(t_stack *stack, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{

	}
}

void	ft_stackiter(t_stack *stack, void (*f)(int, int))
{
	if (!stack || !f)
		return ;
	while (stack)
	{
		write(1, "\nindex: ", 8);
		f(stack->o_index, 1);
		write(1, " nbr: ", 6);
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
	merge_sort(&data.stack_a, data.a_size);
	set_o_index(data.stack_a);
	sort_by_uindex(data.stack_a, data.a_size);
	ft_stackiter(data.stack_a, (*ft_putnbr_fd));
	exit_free(&data);
	return (0);
}
