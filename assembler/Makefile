# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:01:30 by hmaronen          #+#    #+#              #
#    Updated: 2023/01/10 10:56:15 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

NAME = asm
CC = gcc
FLAGS = -g -Wall -Wextra -Werror

SRC_DIR = ./src/
SRC_FILES = asm.c \
			init.c \
			tokenization.c \
			read_header.c \
			vector.c \
			determine_token.c \
			determine_arg.c \
			syntax_analyzer.c \
			generator.c \
			calculations.c \
			int_to_bigendian.c \
			validite_file.c \
			error.c \
			translation.c \
			argument_type_code.c \
			labels.c \
			validate_syntax.c \
			utils.c \
			free_struct.c

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
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I $(INC) $(LIBFT)

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

re : fclean all clean
