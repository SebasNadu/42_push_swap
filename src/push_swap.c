/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 10:45:28 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/06 16:19:43 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

// create atol complete with error handling, and then use it to fill the stack 

long	ft_atol(char *str)
{

}

void	init_data(t_data *data)
{
	(*data).stack_a = NULL;
	(*data).stack_b = NULL;
	(*data).a_size = 0;
	(*data).b_size = 0;
}

void	stack_filler(t_data *data, char **av, int isa_duplicate)
{
	long	nbr;

	while (*av)
	{
		nbr = ft_atol(*av);
	}
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
}
