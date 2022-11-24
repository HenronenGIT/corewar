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

#define LABEL_CHAR ':'
#define HEADER_CHAR '.'
#define STRING_CHAR '"'

/*---------- Main data struct ----------*/
typedef struct s_data
{
	struct s_vec		*vec_info;
	struct s_error_log	*s_error_log;
	struct s_header		*s_header;
} t_data;

typedef struct	s_error_log
{
	size_t	line;
	size_t	column;
}				t_error_log;

/*---------- Dynamic array structure ----------*/
typedef struct s_vec
{
	void **array;
	size_t length;
	size_t space_left;
	size_t space_taken;
} t_vec;


/*---------- Main data struct ----------*/
typedef struct s_input
{
	int		statement;			//statement for any given instruction given as corresponding int found in the header | HENRI
	int		is_label;			// HENRI
	int		current_bytes;
	char	label_name[10];
	int		byte_size;			// full size of every statement as bytes. 0 for labels | HENRI
	int		arg_size[4];		// is size of every arg in bytes | HENRI
	int		arg_type[4];		// is 0 for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	char	*args[4];

	int		argument_type_code;		//argument type code in int | OTTO
	int		arg_values[4];			//arg codes in int | OTTO
	char	*final;					//final bytecode for current statement | OTTO
}	t_input;

int		ft_btoi(char *num);
char	*ft_itoh(int num, int byte_size);

#define LOCATION printf("FILE: |%s| FUNC: |%s| LINE: |%d|\n", __FILE__, __FUNCTION__, __LINE__)
#endif