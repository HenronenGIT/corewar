# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:01:30 by hmaronen          #+#    #+#              #
#    Updated: 2023/01/10 15:11:40 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include vm_srcs.mk

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

NAME = corewar
EXEC_DIR = ../corewar
CC = gcc
FLAGS = -Wall -Wextra -Werror

SRC_DIR = ./src/

SRC = $(addprefix $(SRC_DIR), $(VM_SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(VM_SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = corewar.h op_table.h op.h

INCLS = $(addprefix $(INC_DIR), $(INC_FILES))
INC = ./includes

LIBFT_DIR = ../libft/
LIBFT_LIB = libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ) $(INCLS)
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

re : fclean all 
