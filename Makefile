# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:03:56 by hmaronen          #+#    #+#              #
#    Updated: 2022/12/05 16:04:45 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
FLAGS = -Wall -Wextra -g#-Werror

ASM_DIR = ./asm
VM_DIR = ./corewar

#SRC_DIR = ./src/
SRC_FILES = main.c

#SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

#OBJ_DIR = ./obj/
#OBJ_FILES = $(SRC_FILES:.c=.o)
#OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
INC_FILES = op.h
INC = $(addprefix $(INC_DIR), $(INC_FILES))

LIBFT_DIR = ./libft/
LIBFT_LIB = ./libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all: $(LIBFT) 
	@make -C $(ASM_DIR)
	@make -C $(VM_DIR)

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@mkdir -p $(OBJ_DIR)
# 	@$(CC) $(FLAGS) -c $< -o $@

$(LIBFT):
	@make -C $(LIBFT_DIR) all

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(ASM_DIR) clean
	@make -C $(VM_DIR) clean
	rm *.cor

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(VM_DIR) fclean
	@make -C $(ASM_DIR) fclean

# temp
run:
	@./asm/asm test.s

original:
	./eval_tests/asm test.s
python:
	python3 ./eval_tests/scripts/test_asm.py
re : fclean all clean all
