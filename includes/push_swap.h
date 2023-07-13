/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:54:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/13 12:48:23 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "../libft/includes/libft.h"
# include <stdio.h>

typedef struct s_stack
{
	int				data;
	size_t			u_index;
	size_t			o_index;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_data
{
	t_stack	*stack_a;
	t_stack	*stack_b;
	size_t	a_size;
	size_t	b_size;
}	t_data;

// utils
char	*get_next_word(char	*str, char separator);
char	**ft_split_argv(char *str, char separator);
long	ft_atol(char *str);

// checks
int		check_if_int(char *str);
int		check_if_rep(t_data data, int nbr);

// error_free
void	error_free(t_data *data, char **av, int is_a_dup);
void	free_stack(t_stack *stack, int size);
void	free_vdup(char **av);

// stack_init
void	init_data(t_data *data);
void	stack_filler(t_data *data, char **av, int is_a_dup);
void	set_o_index(t_stack *stack, int size);
void	set_doub_link(t_stack *stack, int size);

// merge_sort
void	merge_sort(t_stack **stack, int size,
			t_stack *(*f_merge)(t_stack *, t_stack *));
t_stack	*merge(t_stack *left, t_stack *right);
t_stack	*merge_by_uindex(t_stack *left, t_stack *right);

// stack_operations
void	operators_parser(t_data *data, char *msg);

#endif
