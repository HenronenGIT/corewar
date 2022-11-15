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
# include "../../libft/includes/libft.h"

typedef struct s_input
{
	int		statement;		//statement for any given instruction given as corresponding int found in the header | HENRI
	char	*arg_1;
	char	*arg_2;
	char	*arg_3;
	int		is_label;		// HENRI
	int		byte_size;		//full size of every statement as bytes. 0 for labels | HENRI
	int		arg_size[4];		//is size of arg1 in bytes | HENRI
	int		*arg_type[4];		// is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI

	char	*statement_code;		//statement code in hexadecimal | OTTO
	char	*argument_type_code;	//argument type code in hexadecimal | OTTO
	char	*arg_1_hex;				//arg 1 code in hexadecimal | OTTO
	char	*arg_2_hex;				//arg 2 code in hexadecimal | OTTO
	char	*arg_3_hex;				//arg 3 code in hexadecimal | OTTO
	char	*final;					//final bytecode for current statement | OTTO
}	t_input;

#endif