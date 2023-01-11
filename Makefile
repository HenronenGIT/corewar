# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/03 13:03:56 by hmaronen          #+#    #+#              #
#    Updated: 2023/01/10 14:46:22 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include ./assembler/asm_srcs.mk
include ./vm/vm_srcs.mk

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
FLAGS = -Wall -Wextra -Werror

ASM = asm
ASM_DIR = ./assembler
ASM_SRC_DIR = ./assembler/src/

VM = corewar
VM_DIR = ./vm
VM_SRC_DIR = ./vm/src/

LIBFT_DIR = ./libft/
LIBFT_LIB = ./libft.a
LIBFT = $(addprefix $(LIBFT_DIR), $(LIBFT_LIB))

ASM_SRC = $(addprefix $(ASM_SRC_DIR), $(ASM_SRC_FILES))
VM_SRC = $(addprefix $(VM_SRC_DIR), $(VM_SRC_FILES))

all: $(ASM) $(VM)

$(ASM): $(LIBFT) $(ASM_SRC)
	@make -C $(ASM_DIR) all
	@mv $(ASM_DIR)/asm ./

$(VM): $(LIBFT) $(VM_SRC)
	@make -C $(VM_DIR) all
	@mv $(VM_DIR)/corewar ./

$(LIBFT):
	@make -C $(LIBFT_DIR) all

clean:
	@make -C $(LIBFT_DIR) clean
	@make -C $(ASM_DIR) clean
	@make -C $(VM_DIR) clean

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@make -C $(ASM_DIR) fclean
	@make -C $(VM_DIR) fclean

valid:
	@python3 ./eval_tests/scripts/valid_asm_tests.py

invalid:
	@python3 ./eval_tests/scripts/invalid_asm_tests.py

re : fclean all  
