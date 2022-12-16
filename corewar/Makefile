# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/15 14:21:56 by wdonnell          #+#    #+#              #
#    Updated: 2022/12/16 10:26:31 by wdonnell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= corewar
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -O2
#CFLAGS		= -Wall -Wextra -Werror -O2 -fsanitize=address -g
SRC_FILES = main.c init_champ_and_data.c init_process_and_fork.c \
			parse.c parse_n.c process.c \
			ids.c utils.c print.c play_game.c get_types.c \
			get_arg_values.c check.c op_util.c \
			op_add_sub.c op_bitwise.c op_fork.c op_load.c op_long_load.c \
			op_misc.c op_store.c

SRCS_DIR	= ./src/
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_FILES))
OBJS_DIR	= ./obj/
OBJS		= $(addprefix $(OBJS_DIR), $(SRC_FILES:.c=.o))
LIB			= -L ../libft -lft
INCLUDES	= -I includes -I ../libft/includes -I ../includes

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) -o $(NAME) $(LIB)

$(LIB):
	make -sC ../libft

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) -c $(CFLAGS) $(INCLUDES) $< -o $@

clean:
	rm -rf $(OBJS_DIR)
	make -C ../libft clean

fclean: clean
	rm -f $(NAME)
	make -C ../libft fclean

re: fclean all
