# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/07 15:44:14 by akilk             #+#    #+#              #
#    Updated: 2022/11/22 14:51:49 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = corewar
CC = gcc
#FLAGS = -Wall #-Wextra -Werror
FLAGS = -Wall -fsanitize=address -g

SRC_DIR = ./src/
SRC_FILES = main.c init.c parse.c data.c process.c \
			parse_flags.c utils.c play_game.c op_table.c \
			get_types.c get_arg_values.c check.c
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
#INCL =  -I includes -I ../libft/includes
INC_FILES = corewar.h op_table.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBFTDIR = ../libft/
LIBFT = ../libft/libft.a
#LIB = -L ../libft #-lft

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(FLAGS) -o $(NAME) $(SRC) -I $(INC_DIR) -L. $(LIBFT)
#	$(CC) $(FLAGS) $(INCL) $(OBJ) -o $(NAME) -L. $(LIBFT)

$(LIBFT):
	make -sC $(LIBFTDIR)

$(OBJ): $(SRC)
	@mkdir -p $(OBJ_DIR)
	@$(CC) -c $(FLAGS) $(INCL) $< -o $@

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

#re : fclean all clean all
re : fclean all
