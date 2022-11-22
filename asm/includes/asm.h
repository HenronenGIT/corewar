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
#define ASM_H

#include <stdio.h>
#include <fcntl.h>
#include <stdbool.h>
#include "../../libft/includes/libft.h"

#define PRINT(s) (printf("FILE: |%s| FUNC: |%s| LINE: |%d|\nValue:%s", __FILE__, __FUNCTION__, __LINE__, s))
#define PRINT_D(d) (printf("FILE: |%s| FUNC: |%s| LINE: |%d|\nValue:%d", __FILE__, __FUNCTION__, __LINE__, d))
#define LOCATION printf("FILE: |%s| FUNC: |%s| LINE: |%d|\n", __FILE__, __FUNCTION__, __LINE__)

/*---------- Error codes ----------*/
#define OPEN_ERR -1
#define ARG_ERR -2
#define MALLOC_ERR -3
#define NULL_ERR -4
#define INVALID_LABEL -5
#define NAME_ERR -6
#define NAME_LEN_ERR -7
#define COMMENT_LEN_ERR -8

#define TEMP_ERR -999 //! TEMP

//! This is copied from op.h header
#define PROG_NAME_LENGTH (128)
#define COMMENT_LENGTH (2048)
#define COREWAR_EXEC_MAGIC 0xea83f3

/*---------- Defines from op.h header ----------*/
#define NAME_CMD_STRING ".name"
#define NAME_CMD_LEN 5
#define COMMENT_CMD_STRING ".comment"
#define COMMENT_CMD_LEN 8

/*---------- Chars for identifying ----------*/
#define LABEL_CHAR ':'
#define HEADER_CHAR '.'
#define STRING_CHAR '"'
#define SEPARATOR_CHAR ','
#define REGISTER_CHAR 'r'
#define DIRECT_CHAR '%'
#define COMMENT_CHAR '#'
#define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"

/*---------- Main data struct ----------*/
typedef struct s_data
{
	struct s_vec *vec_info;
	struct s_vec *vec_tokens;
	struct s_error_log *s_error_log;
	struct s_header *s_header;
} t_data;

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

/*---------- Main data struct ----------*/
typedef struct s_data_cell
{
	int statement;		// statement for any given instruction given as corresponding int found in the header | HENRI
	bool is_label;		// HENRI
	int byte_size;		// full size of every statement as bytes. 0 for labels | HENRI
	int arg_size[3][1]; // is size of every arg in bytes | HENRI
	int arg_type[3][1]; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	int *args[3];

	int *argument_type_code; // argument type code in hexadecimal | OTTO
	int *arg_values[3];		 // arg codes in hexadecimal | OTTO
	char *final;			 // final bytecode for current statement | OTTO
	int current_bytes;		 // current position for calculating distance to labels | OTTO
} t_data_cell;

/* OLD */
// typedef struct s_data_cell
// {
// 	bool is_label; // HENRI
// 	int statement; // 2d array of statement with every argument in its own index | HENRI
// 	char *arg_1;
// 	char *arg_2;
// 	char *arg_3;
// 	int byte_size;	// full size of every statement as bytes. 0 for labels | HENRI
// 	int arg_1_size; // is size of arg1 in bytes | HENRI
// 	int arg_2_size; // is size of arg2 in bytes | HENRI
// 	int arg_3_size; // is size of arg3 in bytes | HENRI
// 	int arg_1_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
// 	int arg_2_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
// 	int arg_3_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
// 	char *statement_code;	  // statement code in hexadecimal | OTTO
// 	char *argument_type_code; // argument type code in hexadecimal | OTTO
// 	char *arg_1_hex;		  // arg 1 code in hexadecimal | OTTO
// 	char *arg_2_hex;		  // arg 2 code in hexadecimal | OTTO
// 	char *arg_3_hex;		  // arg 3 code in hexadecimal | OTTO
// 	char *final;
// } t_data_cell;

//! This is copied fromo op.h header
/*---------- Header Struct ----------*/
typedef struct s_header
{
	unsigned int magic;
	char prog_name[PROG_NAME_LENGTH + 1];
	unsigned int prog_size;
	char comment[COMMENT_LENGTH + 1];
} t_header;

/*---------- enums for identifying type of token ----------*/
typedef enum e_type
{
	NAME,
	COMMENT,
	LABEL,
	STATEMENT,
	SEPARATOR,
	REGISTER,
	DIRECT_LABEL,
	DIRECT,
	INVALID
} t_type;

/*---------- Token struct ----------*/
typedef struct s_token
{
	t_type type;
	char *content;
} t_token;

void error(int error_number);
void read_input(char *input, t_data *s_data);
void read_header(int fd, t_data *s_data);
void lexical_error(t_data *s_data, int error_number);

/*---------- Dynamic 2D array ----------*/
void vec_new_arr(t_vec *dst, size_t len);
void vec_insert(t_vec *dst_vec, void *element);

/*---------- Functions to validate Tokens ----------*/
bool is_label(char *sub_string, t_data *data);
bool is_statement(char *sub_string);
bool is_delimiter(char c);
bool is_register(char *string);
bool is_separator(char c);
bool is_directlabel(t_data *s_data, char *string);
bool	is_direct(t_data *s_data, char *string);

/*---------- Syntax Analyzer ----------*/
void syntax_analysis(t_data *s_data);

/*---------- Printing / debug ----------*/
void print_data(t_data *s_data);
void print_tokens(t_vec *vec_tokens);

#endif