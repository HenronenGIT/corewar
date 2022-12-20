/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:13:58 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/03 13:13:59 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include "../../libft/includes/libft.h"

//! TEMP
# define PRINT(s) (printf("FILE: |%s| FUNC: |%s| LINE: |%d|\nValue:%s", __FILE__, __FUNCTION__, __LINE__, s))
# define PRINT_D(d) (printf("FILE: |%s| FUNC: |%s| LINE: |%d|\nValue:%d", __FILE__, __FUNCTION__, __LINE__, d))
# define LOCATION printf("FILE: |%s| FUNC: |%s| LINE: |%d|\n", __FILE__, __FUNCTION__, __LINE__)
//! TEMP

/*---------- Error codes ----------*/
# define OPEN_ERR -1
# define ARG_ERR -2
# define MALLOC_ERR -3
# define NULL_ERR -4
# define INVALID_LABEL -5
# define NAME_LEN_ERR -6
# define COMMENT_LEN_ERR -7
# define LEXICAL_ERROR -8
# define NAME_COUNT_ERR -9
# define COMMENT_COUNT_ERR -10
# define MISSING_COMMA_ERR -11
# define INVALID_FILE_NAME_ERR -12
# define NO_NL_ERR -13 //TEMP ERROR

/*---------- Syntax errors ----------*/
# define ARG_COUNT_ERR -14
# define INVALID_ARG_ERR -15
# define UNDEFINED_LABEL_ERR -16

# define SYNTAX_ERROR -999 //TEMP ERROR

# define TEMP_ERR -999 //! TEMP

//! This is copied from op.h header
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

/*---------- Defines from op.h header ----------*/
# define NAME_CMD_STRING ".name"
# define NAME_CMD_LEN 5
# define COMMENT_CMD_STRING ".comment"
# define COMMENT_CMD_LEN 8

/*---------- Chars for identifying ----------*/
# define LABEL_CHAR ':'
# define HEADER_CHAR '.'
# define STRING_CHAR '"'
# define SEPARATOR_CHAR ','
# define REGISTER_CHAR 'r'
# define DIRECT_CHAR '%'
# define COMMENT_CHAR '#'
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

# define REG_NUMBER 16

# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8

# define T_REG_SIZE 1
# define T_IND_SIZE 2
# define STATEMENT_SIZE 1

# define REG_SIZE 4
# define DIR_SIZE REG_SIZE

/*---------- Main data struct ----------*/
typedef struct s_data
{
	struct s_vec		*vec_input;
	struct s_vec		*vec_tokens;
	struct s_error_log	*s_error_log;
	struct s_header		*s_header;
	int					champ_size;
} t_data;

/*---------- Collecting information about location ----------*/
typedef struct s_error_log
{
	size_t line;
	size_t column;
} t_error_log;

/*---------- Dynamic array structure ----------*/
typedef struct s_vec
{
	void **array;
	size_t length;
	size_t space_left;
	size_t space_taken;
} t_vec;

/*---------- One of these structs contains info from one statement ----------*/
typedef struct s_data_cell
{
	short arg_count;
	char *label_name;
	int op_code;
	char *args[4];
	int arg_type[4];
	int total_size;	 // full size of every statement as bytes. 0 for labels | HENRI
	int arg_size[4]; // is size of every arg in bytes | HENRI
	int current_bytes;

	int argument_type_code; // argument type code in int | OTTO
	int arg_values[4];		// arg codes in int | OTTO
	char *final;			// final bytecode for current statement | OTTO
} t_input; //! change name to better one

//! This is copied fromo op.h header
/*---------- Header Struct ----------*/
typedef struct s_header
{
	unsigned int magic;
	char prog_name[PROG_NAME_LENGTH + 1];
	unsigned int prog_size;
	char comment[COMMENT_LENGTH + 1];
	bool	name_saved;
	bool	comment_saved;
} t_header;

/*---------- enums for identifying type of token ----------*/
typedef enum e_type
{
	NAME,
	COMMENT,
	LABEL,
	INSTRUCTION,
	SEPARATOR,
	REGISTER,
	DIRECT_LABEL,
	DIRECT,
	INDIRECT,
	NEWLINE,
} t_type;

typedef struct s_op_tab
{
	const char *instruction;
	int op_code;
	int arg_type[3];
	int direct_size;
	// bool arg_type_code;
	int arg_type_code;
	int expected_arg_count;
} t_op_tab;

static const t_op_tab g_op_tab[] = {
	{"live", 1, {T_DIR}, 4, 0, 1},
	{"ld", 2, {T_DIR | T_IND, T_REG}, 4, 1, 2},
	{"st", 3, {T_REG, T_IND | T_REG}, 4, 1, 2},
	{"add", 4, {T_REG, T_REG, T_REG}, 4, 1, 3},
	{"sub", 5, {T_REG, T_REG, T_REG}, 4, 1, 3},
	{"and", 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}, 4, 1, 3},
	{"or", 7, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1, 3},
	{"xor", 8, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 4, 1, 3},
	{"zjmp", 9, {T_DIR}, 2, 0, 1},
	{"ldi", 10, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1, 3},
	{"sti", 11, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 2, 1, 3},
	{"fork", 12, {T_DIR}, 2, 0, 1},
	{"lld", 13, {T_DIR | T_IND, T_REG}, 4, 1, 2},
	{"lldi", 14, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}, 2, 1, 3},
	{"lfork", 15, {T_DIR}, 2, 0, 1},
	{"aff", 16, {T_REG}, 4, 1, 1},
	{NULL, 0, {0}, 0}};

/*---------- Token struct ----------*/
typedef struct s_token
{
	t_type type;
	char *content;
	// location of the token can be saved
} t_token;

/* OTTO */
int ft_btoi(char *num);
char *ft_itoh(int num, int byte_size);
void generator(t_vec *vec_input, int fd);
void make_final(t_input *data, int fd);
void	hex_translator(char *str, int fd, int len);
void	add_magic(int fd);
int		int_to_bigendian(int value, int size);
void	translation(t_data *s_data, char *file_name);

/* File validation */
void	validate_file(char *file_name);
char	*find_file_name(char *s);

/* Inits */

void	init(t_data *data, t_header *header, t_error_log *error_log);
t_input	*init_values(t_input *element);

void	error(int error_number);
void	tokenization(char *input, t_data *s_data);
void	read_header(int fd, t_data *s_data);
void	lexical_error(t_data *s_data);
void	syntax_error(int error_number, t_input *statement, char *label);

/*---------- Dynamic 2D array ----------*/
void	vec_new_arr(t_vec *dst, size_t len);
void	vec_insert(t_vec *dst_vec, void *element);

/*---------- Functions to validate Tokens ----------*/
bool	is_label(t_data *s_data, char *sub_string);
bool	is_statement(char *sub_string);
bool	is_delim(char c);
bool	is_register(char *string);
bool	is_separator(char c);
bool	is_directlabel(t_data *s_data, char *string);
bool	is_direct(t_data *s_data, char *string);
bool	is_indirect(t_data *s_data, char *lexeme);
bool	is_argument(t_type type);

/*---------- Syntax Analyzer ----------*/
void	syntax_analyzer(t_data *s_data);

/*---------- Calculating bytes for statements ----------*/
void calculate_statement_sizes(t_data *s_data);

/*---------- Printing / debug ----------*/
void	print_data(t_data *s_data);
void	print_tokens(t_vec *vec_tokens);

#endif
