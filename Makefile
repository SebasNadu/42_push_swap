# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sebasnadu <johnavar@student.42berlin.de>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/04 19:18:38 by sebasnadu         #+#    #+#              #
#    Updated: 2023/10/06 22:05:22 by sebasnadu        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COLORS
DEFAULT = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

NAME = push_swap

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a
LFT_FLAGS	= -L $(LIBFT_DIR) -lft

INCLUDES	= -I includes -I $(LIBFT_DIR)/includes/
CC			= cc
# CLAGS		= -Wall -Wextra -Werror
CFLAGS		= -Wall -Wextra -Werror -g3 -fsanitize=address
RM			= rm -f
PRINTF 		= printf

DIR_SRC		= src
DIR_OBJS	= objs
SRC			= $(wildcard $(DIR_SRC)/*.c)
OBJS		= $(SRC:$(DIR_SRC)/%.c=$(DIR_OBJS)/%.o)

# Progress vars
SRC_COUNT_TOT := $(shell expr $(shell echo -n $(SRC) | wc -w) - $(shell ls -l $(OBJ_DIR) 2>&1 | grep ".o" | wc -l) + 1)
ifeq ($(shell test $(SRC_COUNT_TOT) -le 0; echo $$?),0)
	SRC_COUNT_TOT := $(shell echo -n $(SRC) | wc -w)
endif
SRC_COUNT := 0
SRC_PCT = $(shell expr 100 \* $(SRC_COUNT) / $(SRC_COUNT_TOT))

$(DIR_OBJS)/%.o: $(DIR_SRC)/%.c
	@mkdir -p $(DIR_OBJS)
	@$(eval SRC_COUNT = $(shell expr $(SRC_COUNT) + 1))
	@$(PRINTF) "\r%100s\r[ %d/%d (%d%%) ] Compiling $(BLUE)$<$(DEFAULT)..." "" $(SRC_COUNT) $(SRC_COUNT_TOT) $(SRC_PCT)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FLAGS) $(LFT_FLAGS)
	@$(PRINTF) "\r%100s\r$(GREEN)$(NAME) is up to date!$(DEFAULT)\n"

clean:
	@$(PRINTF) "$(CYAN)Cleaning up object files in $(DIR_OBJS)...$(DEFAULT)\n"
	@make clean -C $(LIBFT_DIR)
	@$(RM) $(OBJS)
	@$(RM) -r $(DIR_OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)
	@$(PRINTF) "$(CYAN)Removed $(LIBFT)$(DEFAULT)\n"
	@$(PRINTF) "$(CYAN)Removed $(NAME)$(DEFAULT)\n"
	
re: fclean all

norminette: | $(LIBFT_DIR)
	@$(PRINTF) "$(CYAN)\nChecking norm for $(NAME)...$(DEFAULT)\n"
	@norminette -R CheckForbiddenSourceHeader $(DIR_SRC) includes
	@make norminette -C libft

.PHONY: all clean fclean re
