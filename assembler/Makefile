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

include asm_srcs.mk

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

NAME = asm
EXEC_DIR = ../asm
CC = gcc
FLAGS = -g -Wall -Wextra -Werror

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(ASM_SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(ASM_SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = asm.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBFT_DIR = ../libft/
LIBFT_LIB = libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INC)
	@echo "$(CYELLOW)Compiling $(NAME) program$(CEND)"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I $(INC) $(LIBFT)
	@echo "$(CGREEN)OK$(CEND)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) all

clean:
	@echo "$(CYELLOW)Removing $(NAME) object folder$(CEND)"
	@rm -rf $(OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean: clean
	@echo "$(CYELLOW)Removing $(NAME) program$(CEND)"
	@rm -rf $(EXEC_DIR)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean
