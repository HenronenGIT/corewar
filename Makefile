
]CYELLOW=\033[0;33m
CEND=\033[0m
CGREEN=\033[0;32m

CC = gcc
NAME = corewar
#NAME = asm
FLAGS = -Wall -Wextra #-Werror

SRC_DIR = ./src/
SRC_FILES = main.c \

SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

OBJ_DIR = ./obj/
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))

INC_DIR = ./includes/
#INC_FILES = 
INC = $(addprefix $(INC_DIR), $(INC_FILES))

#LIBPRINT_DIR = libft/
#LIBPRINT_LIB = libft.a
#LIBPRINT = $(addprefix $(LIBPRINT_DIR), $(LIBPRINT_LIB))

all : $(NAME)

$(NAME): $(OBJ) $(INC)
	@make -C $(LIBPRINT_DIR)
	@echo "$(CYELLOW)Compiling $(NAME)$(CEND)"
	@$(CC) -o $(NAME) $(FLAGS) $(OBJ) -I libft/includes/ -I ./includes/ -L. $(LIBPRINT)
	@echo "$(CGREEN)OK$(CEND)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c $< -o $@

clean :
	@make -C $(LIBPRINT_DIR) clean
	@echo "$(CYELLOW)Removing $(NAME) object folder$(CEND)"
	@rm -rf $(OBJ_DIR)
	@echo "$(CGREEN)OK$(CEND)"

fclean : clean
	@make -C $(LIBPRINT_DIR) fclean
	@echo "$(CYELLOW)Removing $(NAME)$(CEND)"
	@rm -rf $(NAME)
	@echo "$(CGREEN)OK$(CEND)"

re : fclean all clean all
