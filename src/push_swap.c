/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/12 23:02:20 by sebasnadu        ###   ########.fr       */
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

t_stack	*merge_by_uindex(t_stack *left, t_stack *right)
{
	t_stack	*result;

	if (!left)
		return (right);
	if (!right)
		return (left);
	if (left->u_index <= right->u_index)
	{
		result = left;
		result->next = merge_by_uindex(left->next, right);
	}
	else
	{
		result = right;
		result->next = merge_by_uindex(left, right->next);
	}
	return (result);
}

void	merge_sort(t_stack **stack, int size, t_stack *(*f_merge)(t_stack *, t_stack *))
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
	merge_sort(&left, size / 2, f_merge);
	merge_sort(&right, size - (size / 2), f_merge);
	*stack = f_merge(left, right);
	(*stack)->prev = NULL;
}

void	set_o_index(t_stack *stack)
{
	int		i;
	t_stack	*tmp;

	i = 0;
	tmp = stack;
	while (tmp->next)
	{
		tmp->o_index = i;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		++i;
	}
	tmp->o_index = i;
	stack->prev = tmp;
	tmp->next = stack;
}

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
	set_o_index(data.stack_a);
	merge_sort(&data.stack_a, data.a_size, merge_by_uindex);
	ft_stackiter(data.stack_a, data.a_size, (*ft_putnbr_fd));
	exit_free(&data);
	return (0);
}
