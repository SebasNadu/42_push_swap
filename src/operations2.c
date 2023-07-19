/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 12:24:38 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/19 16:23:13 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

size_t	psh(t_data *data, char *msg)
{
	if (data->b_size && ft_strncmp(msg, "pa", 2) == 0)
		// && ft_strncmp(data->prev_op, "pb", 2) != 0)
	{
		return (operations_parser(data, "pa"));
	}
	if (data->a_size && ft_strncmp(msg, "pb", 2) == 0)
		// && ft_strncmp(data->prev_op, "pa", 2) != 0)
		return (operations_parser(data, "pb"));
	return (0);
}

size_t	swp(t_data *data, char *msg, size_t sec)
{
	if (ft_strncmp(msg, "sa", 2) == 0)
	{
		if (data->a_size == 2 && ft_strncmp(data->prev_op, "rb", 2) == 0)
			return (operations_parser(data, "ra"));
		else if (data->a_size == 2 && ft_strncmp(data->prev_op, "rrb", 3) == 0)
			return (operations_parser(data, "rra"));
		else if (data->a_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "sa", 2) != 0))
			return (operations_parser(data, "sa"));
	}
	else if (ft_strncmp(msg, "sb", 2) == 0)
	{
		if (data->b_size == 2 && ft_strncmp(data->prev_op, "ra", 2) == 0)
			return (operations_parser(data, "rb"));
		else if (data->b_size == 2 && ft_strncmp(data->prev_op, "rra", 3) == 0)
			return (operations_parser(data, "rrb"));
		else if (data->b_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "sb", 2) != 0))
			return (operations_parser(data, "sb"));
	}
	return (0);
}

size_t	rot(t_data *data, char *msg, size_t sec)
{
	if (ft_strncmp(msg, "ra", 2) == 0)
	{	
		if (data->a_size == 2 && ft_strncmp(data->prev_op, "sb", 2) == 0)
			return (operations_parser(data, "sa"));
		else if (data->a_size == 2 && ft_strncmp(data->prev_op, "rrb", 3) == 0)
			return (operations_parser(data, "rra"));
		else if (data->a_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "rra", 3) != 0))
			return (operations_parser(data, "ra"));
	}
	else if (ft_strncmp(msg, "rb", 2) == 0)
	{
		if (data->b_size == 2 && ft_strncmp(data->prev_op, "sa", 2) == 0)
			return (operations_parser(data, "sb"));
		else if (data->b_size == 2 && ft_strncmp(data->prev_op, "rra", 3) == 0)
			return (operations_parser(data, "rrb"));
		else if (data->b_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "rrb", 3) != 0))
			return (operations_parser(data, "rb"));
	}
	return (0);
}

size_t	rrot(t_data *data, char *msg, size_t sec)
{
	if (ft_strncmp(msg, "rra", 3) == 0)
	{	
		if (data->a_size == 2 && ft_strncmp(data->prev_op, "sb", 2) == 0)
			return (operations_parser(data, "sa"));
		else if (data->a_size == 2 && ft_strncmp(data->prev_op, "rb", 2) == 0)
			return (operations_parser(data, "ra"));
		else if (data->a_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "ra", 2) != 0))
			return (operations_parser(data, "rra"));
	}
	else if (ft_strncmp(msg, "rrb", 3) == 0)
	{
		if (data->b_size == 2 && ft_strncmp(data->prev_op, "sa", 2) == 0)
			return (operations_parser(data, "sb"));
		else if (data->b_size == 2 && ft_strncmp(data->prev_op, "ra", 2) == 0)
			return (operations_parser(data, "rb"));
		else if (data->b_size >= 2 && (!sec
				|| ft_strncmp(data->prev_op, "rb", 2) != 0))
			return (operations_parser(data, "rrb"));
	}
	return (0);
}
