# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 19:18:38 by sebasnadu         #+#    #+#              #
#    Updated: 2023/07/04 19:44:32 by sebasnadu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LFT_FLAGS	= -L $(LIBFT_DIR) -lft

INCLUDES	= -I includes -I $(LIBFT_DIR)/includes/
CC			= cc
# CFLAGS		= -Wall -Wextra -Werror
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			= rm -f

DIR_SRC		= src
DIR_OBJS	= objs
SRC			= $(wildcard $(DIR_SRC)/*.c)
OBJS		= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJS)/%.o)

$(DIR_OBJS)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_OBJS)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS) $(LFT_FLAGS)

clean:
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@$(RM) $(OBJS)
	@$(RM) -r $(DIR_OBJS)

fclean: clean
	@make fclean --no-print-directory -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re
