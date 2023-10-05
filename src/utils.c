/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 13:25:04 by sebasnadu         #+#    #+#             */
/*   Updated: 2023/10/05 19:26:42 by johnavar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

long	ft_atol(char *str)
{
	long	nbr;
	int		sign;

	if (!str)
		return (0);
	sign = 1;
	nbr = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	while (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		++str;
	}
	while (*str >= '0' && *str <= '9')
	{
		nbr = (nbr * 10) + (*str - '0');
		++str;
	}
	return (nbr * sign);
}

static int	count_words(char *str, char separator)
{
	int	count;
	int	is_insideword;

	count = 0;
	while (*str)
	{
		is_insideword = 0;
		while (*str == separator)
			++str;
		while (*str && *str != separator)
		{
			if (!is_insideword)
			{
				++count;
				is_insideword = 1;
			}
			++str;
		}
	}
	return (count);
}

char	*get_next_word(char	*str, char separator)
{
	static int	start = 0;
	char		*next_str;
	int			end;
	int			i;

	end = 0;
	while (str[start] == separator)
		++start;
	while (str[start + end] != separator && str[start + end])
		++end;
	next_str = malloc((end + 1) * sizeof(char));
	if (next_str == NULL)
		return (NULL);
	i = 0;
	while (str[start] != separator && str[start])
		next_str[i++] = str[start++];
	next_str[i] = '\0';
	return (next_str);
}

char	**ft_split_argv(char *str, char separator)
{
	char	**strv;
	int		words_count;
	int		i;

	words_count = count_words(str, separator);
	strv = (char **)malloc(sizeof(char *) * (words_count + 2));
	if (strv == NULL)
		return (NULL);
	i = 0;
	while (words_count-- >= 0)
	{
		if (i == 0)
		{
			strv[i] = malloc(1 * sizeof(char));
			if (strv[i] == NULL)
				return (NULL);
			strv[i++][0] = '\0';
			continue ;
		}
		strv[i++] = get_next_word(str, separator);
	}
	strv[i] = NULL;
	return (strv);
}
