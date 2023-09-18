/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:54:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/09/18 15:51:59 by sebasnadu        ###   ########.fr       */
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
	size_t	f_s;
	char	*prev_op;
}	t_data;

// utils
char	*get_next_word(char	*str, char separator);
char	**ft_split_argv(char *str, char separator);
long	ft_atol(char *str);

// checks
int		check_if_int(char *str);
int		check_if_dup(t_data data, int nbr);
int		check_if_sorted(t_stack *stack, int size);

// error_free
void	error_free(t_data *data, char **av, int is_a_dup);
void	free_stack(t_stack *stack, int size);
void	free_vdup(char **av);

// stack_init
void	init_data(t_data *data);
void	stack_filler(t_data *data, char **av, int is_a_dup);

// stack_setters
void	set_o_index(t_stack *stack, int size);
void	set_doub_link(t_stack **stack, int size);
void	set_doub_circular_link(t_stack **stack, int size);

// merge_sort
void	merge_sort(t_stack **stack, int size,
			t_stack *(*f_merge)(t_stack *, t_stack *));
t_stack	*merge(t_stack *left, t_stack *right);
t_stack	*merge_by_uindex(t_stack *left, t_stack *right);

// operations_parsers
size_t	operations_parser(t_data *data, char *msg);

// operations
void	push(t_stack **dest, t_stack **src, size_t *dest_size,
			size_t *src_size);
void	rotate(t_stack **stack, int is_rev);
void	swap(t_stack **stack, int size);

// push_swap
void	push_swap(t_data *data);
void	sort_three(t_data *data);
void	sort_four(t_data *data);
void	sort_five(t_data *data);

// radix_sort
void	binary_radix_sort(t_data *data, size_t iter_length);

// push_swap_utils
size_t	find_lowest(t_stack *stack, int size);
size_t	find_highest(t_stack *stack, int size);
size_t	leftmost_bit(size_t nbr);
int		find_ordered(t_stack *stack, size_t size, char c);

// greedy_sort
void	greedy_sort(t_data *data);

// greedy_sort_controller
void	get_min_rotate(t_data *data, int *a, int *b);
void	rotate_same(t_data *data, int *a, int *b);
void	rotate_b(t_data *data, int b);
void	rotate_a(t_data *data, int a);

// greedy_sort_utils
int		set_a_pos(int num, t_data *data);
int		set_over_pos(t_data *data);

// test
void	ft_stackiter(t_stack *stack, int size, void (*f)(int, int));

#endif
