/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 13:13:58 by hmaronen          #+#    #+#             */
/*   Updated: 2023/01/10 11:03:23 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include <fcntl.h>
# include <stdbool.h>
# include "../../libft/includes/libft.h"

/*---------- Error codes ----------*/
# define OPEN_ERR -1
# define ARGV_ERR -2
# define MALLOC_ERR -3
# define NULL_ERR -4
# define INVALID_LABEL -5
# define NAME_LEN_ERR -6
# define COMMENT_LEN_ERR -7
# define LEXICAL_ERROR -8
# define NAME_COUNT_ERR -9
# define COMMENT_COUNT_ERR -10
# define MISSING_COMMA_ERR -12
# define INVALID_FILE_NAME_ERR -13
# define MISSING_CHAMP_ERR -14

/*---------- Syntax errors ----------*/
# define NO_NL_ERR -15
# define ARG_COUNT_ERR -16
# define ARG_ERR -17
# define UNDEFINED_LABEL_ERR -18
# define INVALID_TOKEN_ERR -19
# define INVALID_EOL_ERR -20
# define SYNTAX_ERROR -21

/*---------- Header defines ----------*/
# define NAME_STRING ".name"
# define NAME_CMD_LEN 5
# define COMMENT_STRING ".comment"
# define COMMENT_CMD_LEN 8
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

/*---------- Chars for identifying ----------*/
# define LABEL_CHAR ':'
# define HEADER_CHAR '.'
# define STRING_CHAR '"'
# define SEPARATOR_CHAR ','
# define REGISTER_CHAR 'r'
# define DIRECT_CHAR '%'
# define COMMENT_CHAR '#'
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

/*---------- Argument defines ----------*/
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
}	t_data;

/*---------- Collecting information about location ----------*/
typedef struct s_error_log
{
	size_t	line;
	size_t	column;
}	t_error_log;

/*---------- Dynamic array structure ----------*/
typedef struct s_vec
{
	void	**array;
	size_t	length;
	size_t	space_left;
	size_t	space_taken;
}	t_vec;

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
}	t_type;

/*---------- Token struct ----------*/
typedef struct s_token
{
	t_type	type;
	char	*content;
	int		line;
	int		column;
}	t_token;

/*---------- One of these structs contains info from one statement ----------*/
typedef struct s_statement
{
	short	arg_count;
	char	*label_name;
	int		op_code;
	char	*args[4];
	int		arg_type[4];
	int		total_size;
	int		arg_size[4];
	int		current_bytes;
	int		argument_type_code;
	int		arg_values[4];
	char	*final;
}	t_stmnt;

/*---------- Header data ----------*/
typedef struct s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
	bool			name_saved;
	bool			comment_saved;
}	t_header;

/*---------- Struct for fetching data from op_tab ----------*/
typedef struct s_op_tab
{
	const char	*instruction;
	int			op_code;
	int			arg_type[3];
	int			direct_size;
	int			arg_type_code;
	int			expected_arg_count;
}	t_op_tab;

static const t_op_tab	g_op_tab[] = {
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
{NULL, 0, {0}, 0, 0, 0}};

/*---------- Struct for fetching data from op_tab ----------*/
void	validate_file(char *file_name);
char	*find_file_name(char *s);

/*---------- Init ----------*/
void	init(t_data *data, t_header *header, t_error_log *error_log);
t_stmnt	*init_values(t_stmnt *element);

/*---------- Tokenization ----------*/
void	tokenization(char *input, t_data *s_data);
void	read_header(int fd, t_data *s_data);
char	*save_to_buffer(t_data *s_data, char *string, int fd);
void	save_header(t_data *s_data, char *buffer, t_type type);
void	lexical_error(t_data *s_data);

/*---------- Syntax Analyzer ----------*/
void	syntax_analyzer(t_data *s_data);
void	validate_syntax(t_data *s_data, t_token *curr_token, t_type last_token);
void	syntax_error(int error_number, t_error_log *error_log, \
					const char *str, t_token *token);

/*---------- Calculating bytes for statements ----------*/
void	calculate_statement_sizes(t_data *s_data);

/*---------- Translation ----------*/
void	generate_bytecode(t_vec *vec_input, int fd);
void	hex_translator(char *str, int fd, int len);
int		int_to_bigendian(int value, int size);
void	translation(t_data *s_data, char *file_name);
void	find_label_addr(t_stmnt **array, char *curr_label_name, \
						int curr_arg, int curr_struct);
int		compare_labels(char *original_label, char *current_label);
int		is_label_call(char *current_arg);
void	save_atc(t_stmnt *data);

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

/*---------- Utils ----------*/
void	error(int error_number);
int		lookup(const char *string);
int		contains_invalid_characters(t_data *s_data, char *lexeme);
void	reel_to_end(t_data *s_data, char *string);
void	usage(void);
char	*decide_destination(t_data *s_data, t_type type);

#endif
