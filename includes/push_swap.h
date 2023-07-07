/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 19:54:36 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/07/08 00:39:45 by sebasnadu        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include "../libft/includes/libft.h"

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
void	free_stack(t_stack *stack);
void	free_vdup(char **av);

#endif
