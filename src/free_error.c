/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 22:23:50 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/10/12 16:57:41 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

void	free_vdup(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		free(av[i]);
		av[i] = NULL;
		i++;
	}
	free(av);
	av = NULL;
}

void	free_stack(t_stack *stack, int size)
{
	t_stack	*next_node;
	t_stack	*current;
	int		i;

	if (!stack || size == 0)
		return ;
	i = 0;
	current = stack;
	next_node = stack->next;
	while (next_node != stack && i < size - 1)
	{
		free(current);
		current = next_node;
		next_node = current->next;
		++i;
	}
	free(current);
}

void	error_free(t_data *data, char **av, int isa_duplicate)
{
	if ((*data).stack_a)
		free_stack((*data).stack_a, (*data).a_size);
	if (isa_duplicate)
		free_vdup(av);
	ft_putstr_fd("Error\n", 2);
	exit(EXIT_FAILURE);
}
