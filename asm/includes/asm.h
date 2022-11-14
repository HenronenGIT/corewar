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
#define LOCATION printf("FILE: |%s| FUNC: |%s| LINE: |%d|\n", __FILE__, __FUNCTION__, __LINE__)

/*---------- Error codes ----------*/
#define OPEN_ERR -1
#define ARG_ERR -2
#define MALLOC_ERR -3
#define NULL_ERR -4
#define INVALID_LABEL -5

//! This is copied from op.h header
#define PROG_NAME_LENGTH (128)
#define COMMENT_LENGTH (2048)
#define COREWAR_EXEC_MAGIC 0xea83f3

/*---------- Defines from op.h header ----------*/
#define NAME_CMD_STRING ".name"
#define COMMENT_CMD_STRING ".comment"
#define LABEL_CHAR ':'

/*---------- Dynamic array structure ----------*/
typedef struct s_vec
{
	void **array;
	size_t length;
	size_t space_left;
	size_t space_taken;
} t_vec;

/*---------- Main data struct ----------*/
typedef struct s_data
{
	t_vec *vec_info;
} t_data;

/*---------- Main data struct ----------*/
typedef struct s_input
{
	int statement; // 2d array of statement with every argument in its own index | HENRI
	char *arg_1;
	char *arg_2;
	char *arg_3;
	int is_label;	// HENRI
	int byte_size;	// full size of every statement as bytes. 0 for labels | HENRI
	int arg_1_size; // is size of arg1 in bytes | HENRI
	int arg_2_size; // is size of arg2 in bytes | HENRI
	int arg_3_size; // is size of arg3 in bytes | HENRI
	int arg_1_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	int arg_2_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	int arg_3_type; // is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI

	char *statement_code;	  // statement code in hexadecimal | OTTO
	char *argument_type_code; // argument type code in hexadecimal | OTTO
	char *arg_1_hex;		  // arg 1 code in hexadecimal | OTTO
	char *arg_2_hex;		  // arg 2 code in hexadecimal | OTTO
	char *arg_3_hex;		  // arg 3 code in hexadecimal | OTTO
	char *final;
} t_input;

//! This is copied fromo op.h header
/*---------- Header Struct ----------*/
typedef struct s_header
{
	unsigned int magic;
	char prog_name[PROG_NAME_LENGTH + 1];
	unsigned int prog_size;
	char comment[COMMENT_LENGTH + 1];
} t_header;

typedef enum e_type
{
	NAME,
	COMMENT,
	STATEMENT,
	OPERATOR,
	LABEL,

} t_type;

/*---------- Token struct ----------*/
typedef struct s_token
{
	t_type type;
	char *content;
	/* data */
} t_token;

void error(int error_number);
void read_input(char *input, t_data *s_data);

/*---------- Dynamic 2D array ----------*/
void vec_new_arr(t_vec *dst, size_t len);
void vec_insert(t_vec *dst_vec, void *element);

/*---------- Functions to validate Tokens ----------*/
bool is_label(char *sub_string);
bool is_statement(char *sub_string);
bool is_delimiter(char c);

#endif