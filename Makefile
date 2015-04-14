#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/14 20:02:40 by mle-roy           #+#    #+#              #
#    Updated: 2015/04/14 20:35:59 by mle-roy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

# NAME = asm

# SRC_DIR = src_asm

# SRC_S = $(SRC_DIR)/main.c \
# 		$(SRC_DIR)/compileFile.c \
# 		$(SRC_DIR)/treatFile.c


# OBJ_S = $(SRC_S:.c=.o)


# FLAGS = -g3 -Wall -Wextra -Werror

# all: build $(NAME) finish

# build:
# 	@make -C libft

# $(NAME): $(OBJ_S)
# 	@gcc $(OBJ_S) -L libft -lft -o $(NAME)


# %.o: %.c
# 	@gcc $(FLAGS) -c -I libft/includes -I includes_asm $<

# clean:
# 	@rm -f $(OBJ_S)
# 	@make -C libft/ clean

# fclean: clean
# 	@rm -f ../$(NAME)
# 	@make -C libft/ fclean

# re: fclean all

# finish:
# 	@(echo "[\033[32m$(NAME)\033[00m]")

# .PHONY: all build clean fclean re

NAME				=		asm

SRC_DIR				=		src_asm
INCLUDE_DIR			=		includes_asm

OBJ_DIR				=		objs

COMPILER			=		gcc
CFLAGS				=		-g3 -Wall -Wextra -Werror -c \
							-I$(INCLUDE_DIR) -I libft/includes
LFLAGS				=		-o

SRC					=		main.c		\
							compileFile.c \
							treatFile.c

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: build $(NAME)


build:
	@make -C libft

$(NAME): $(OBJ)
	$(COMPILER) -L libft -lft $(LFLAGS) $@ $^

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(COMPILER) $(CFLAGS) $< -o $@


clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
