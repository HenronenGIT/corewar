# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:03:56 by hmaronen          #+#    #+#              #
#    Updated: 2022/12/21 10:26:21 by okoponen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
FLAGS = -Wall -Wextra -g -Werror

ASM_DIR = ./assembler
VM_DIR = ./vm

LIBFT_DIR = ./libft/
LIBFT_LIB = ./libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

all: $(LIBFT) 
	@make -C $(ASM_DIR)
	@make -C $(VM_DIR)
	mv $(ASM_DIR)/asm ./
	mv $(VM_DIR)/corewar ./

$(LIBFT):
	@make -C $(LIBFT_DIR) all

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(ASM_DIR) clean
	@make -C $(VM_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean

valid:
	@python3 ./eval_tests/scripts/valid_asm_tests.py

invalid:
	@python3 ./eval_tests/scripts/invalid_asm_tests.py

re : all fclean clean
