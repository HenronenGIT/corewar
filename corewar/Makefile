# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:44:14 by akilk             #+#    #+#              #
#    Updated: 2022/11/10 12:38:23 by akilk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/
SRC_FILES = main.c init.c parse.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = corewar.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBFTDIR = ../libft/
LIBFT = ../libft/libft.a

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(SRC) -I $(INC) -L. $(LIBFT)

$(LIBFT):
	make -sC $(LIBFTDIR)

$(OBJ): $(SRC)
	@mkdir -p $(OBJ_DIR)
	@gcc $(FLAGS) -c $< -o $@

clean:
	@make -C $(LIBFTDIR) clean
	@echo "$(CYELLOW)Removing $(NAME) object folder$(CEND)"
	@rm -rf $(OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean: clean
	@make -C $(LIBFTDIR) fclean
	@echo "$(CYELLOW)Removing $(NAME)$(CEND)"
	@rm -rf $(NAME)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean all
