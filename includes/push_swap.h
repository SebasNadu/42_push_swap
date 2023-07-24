/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:54:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/24 11:22:30 by sebasnadu        ###   ########.fr       */
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

// radix_sort
void	binary_radix_sort(t_data *data, size_t iter_length);

// push_swap_utils
size_t	find_lowest(t_stack *stack, int size);
size_t	find_highest(t_stack *stack, int size);
size_t	leftmost_bit(size_t nbr);
int		find_ordered(t_stack *stack, size_t size, char c);

// TOCOMPLETE quick sort
void	quick_sort_init(t_data *data, size_t low, size_t high);
void	last_sort_b(t_data *data, size_t low, size_t high);
void	last_sort_a(t_data *data, size_t low, size_t high);
void	quick_sort_b(t_data *data, size_t high, size_t low, size_t is_end);
void	quick_sort_a(t_data *data, size_t low, size_t high, size_t is_end);
void	next_sort(t_data *data, size_t low, size_t high, size_t iws_end);
void	twin_insert_sort(t_data *data, size_t low, size_t high);
void	insert_sort_a(t_data *data, size_t high, size_t low);
void	insert_sort_b(t_data *data, size_t high, size_t low);
void	five_sort_a(t_data *data, size_t low, size_t high);
void	three_sort(t_data *data, size_t low, size_t high);
size_t	swap_bottoms(t_data *d, t_stack *s_a, t_stack *s_b);
size_t	swap_tops(t_data *d, t_stack *s_a, t_stack *s_b);
void	search_target_a(t_data *data, size_t index, size_t next);
void	search_target_b(t_data *data, size_t index, size_t next);
int		sorted_by(t_data *data, size_t is_a, size_t low);
size_t	find_pos(t_stack *stack, size_t size, size_t index);

// TOCOMPLETE operations 2
size_t	psh(t_data *data, char *msg);
size_t	swp(t_data *data, char *msg, size_t sec);
size_t	rot(t_data *data, char *msg, size_t sec);
size_t	rrot(t_data *data, char *msg, size_t sec);

// test
void	ft_stackiter(t_stack *stack, int size, void (*f)(int, int));

#endif
