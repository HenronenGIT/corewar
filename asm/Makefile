# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:01:30 by hmaronen          #+#    #+#              #
#    Updated: 2022/11/03 13:03:48 by hmaronen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

NAME = asm
CC = gcc
FLAGS = -g -Wall -fsanitize=address#-Wextra #-Werror

SRC_DIR = ./src/
SRC_FILES = asm.c \
			init.c \
			read_input.c \
			read_header.c \
			vector.c \
			is_functions.c \
			lexical_error.c \
			validation.c \
			syntax_analyzer.c \
			debug.c \
			generator.c \
			ft_btoi.c \
			ft_itoh.c \
			hex_translator.c \
			calculations.c \
			int_to_bigendian.c

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = asm.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBFT_DIR = ../libft/
LIBFT_LIB = libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all: $(NAME)

$(NAME): $(OBJ) $(INC)
	@echo "$(CYELLOW)Compiling $(NAME) program$(CEND)"
#	@$(CC) -o $(NAME) $(FLAGS) $(SRC) -I $(INC) -L. $(LIBFT)
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I $(INC) $(LIBFT)

#	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBFT)
	@echo "$(CGREEN)OK$(CEND)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@echo "$(CYELLOW)Removing $(NAME) object folder$(CEND)"
	@rm -rf $(OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean: clean
	@echo "$(CYELLOW)Removing $(NAME) program$(CEND)"
	@rm -rf $(NAME)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean all
