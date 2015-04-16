#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mle-roy <mle-roy@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/14 20:02:40 by mle-roy           #+#    #+#              #
#    Updated: 2015/04/15 18:21:49 by mle-roy          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME				=		asm

SRC_DIR				=		src_asm
INCLUDE_DIR			=		includes_asm

OBJ_DIR				=		objs

COMPILER			=		gcc
CFLAGS				=		-g3 -Wall -Wextra -Werror -c \
							-I $(INCLUDE_DIR) -I libft/includes
LFLAGS				=		-o

SRC					=		main.c		\
							compileFile.c \
							treatFile.c \
							cleanTokens.c \
							findLabels.c \
							errorAsm.c

OBJ					=		$(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))

all: build $(NAME) finish


build:
	@make -C libft

$(NAME): $(OBJ)
	$(COMPILER) $(LFLAGS) $@ $^ -L libft -lft

$(OBJ): | $(OBJ_DIR)

$(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(COMPILER) $(CFLAGS) $< -o $@


clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)
	@make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	@make -C libft/ fclean

finish:
	@(echo "[\033[32m$(NAME)\033[00m]")

re: fclean all

.PHONY: all build clean fclean re
