# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 14:21:56 by wdonnell          #+#    #+#              #
#    Updated: 2022/12/16 13:28:35 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include vm_srcs.mk

NAME		= corewar
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2

SRCS_DIR	= ./src/
SRCS		= $(addprefix $(SRCS_DIR), $(VM_SRC_FILES))
OBJS_DIR	= ./obj/
OBJS		= $(addprefix $(OBJS_DIR), $(VM_SRC_FILES:.c=.o))
LIB			= -L ../libft -lft
INCLUDES	= -I includes -I ../libft/includes -I ../includes

CYELLOW=\033[0;33m
CGREEN=\033[0;32m
CEND=\033[0m

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIB)

$(LIB):
	make -sC ../libft

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@
	
clean:
	rm -rf $(OBJS_DIR)
	make -C ../libft clean

fclean: clean
	rm -f ../$(NAME)
	make -C ../libft fclean

re: fclean all
