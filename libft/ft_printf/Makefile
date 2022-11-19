# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/14 11:28:02 by hmaronen          #+#    #+#              #
#    Updated: 2022/02/14 11:28:05 by hmaronen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

NAME = libftprintf.a

CC = gcc -g
FLAGS = #-Wall -Wextra -Werror
DB_FLAG = -g $(FLAGS)
AR = ar rcs

SRC = $(addprefix ./src/,	ft_printf.c 		\
							handlers.c			\
							handlers_2.c		\
							tools.c				\
							length_modifiers.c	\
							flags.c				\
							padding.c			\
							handle_float.c)
	
OBJ =	ft_printf.o			\
		handlers.o			\
		handlers_2.o		\
		tools.o				\
		length_modifiers.o	\
		flags.o				\
		padding.o			\
		handle_float.o

LIBFT_H = -I ../includes
PRINTF_H = -I ./
HEADERS = $(LIBFT_H) $(PRINTF_H)

FILE_PATH = ./eval_tests/

LIB = -L ./libft -lft

RM = /bin/rm -f

all: $(NAME)

$(NAME): $(SRC)
	@echo "$(CYELLOW)Compiling $(NAME)$(CEND)"
	@$(CC) $(FLAGS) $(HEADERS) -c $(SRC)
	@echo "$(CGREEN)OK$(CEND)"

clean:
	@echo "$(CYELLOW)Deleting ft_printf .o files$(CEND)"
	@$(RM) $(OBJ)
	@echo "$(CGREEN)OK$(CEND)"

fclean: clean
	@echo "$(CYELLOW)Deleting ft_printf library$(CEND)"
	@/bin/rm -f $(NAME)
	CEND

re: fclean all

test: $(SRC)
	@$(CC) $(FLAGS) $(NAME) ./eval_tests/main.c $(PRINTF_H) -D "ORIGINAL"
	@./a.out
	@$(CC) $(FLAGS) $(NAME) ./eval_tests/main.c $(PRINTF_H)
	@./a.out

sanitize: fclean
	@make -C ./libft/ $(LIBFT_H) fclean && make -C ./libft/ $(LIBFT_H) leaks
	@$(CC) -g -fsanitize=address $(FLAGS) -I ./ -c $(SRC)
	@ar rc -s $(NAME) *.o ./libft/*.o
	@$(CC) $(FLAGS) -g -fsanitize=address $(NAME) ./eval_tests/main.c $(PRINTF_H) -D "ORIGINAL"
	@./a.out
	@$(CC) $(FLAGS) -g -fsanitize=address $(NAME) ./eval_tests/main.c $(PRINTF_H)
	@./a.out

.PHONY: all clean fclean re
