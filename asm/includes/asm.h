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
	char	**statement;	//2d array of statement with every argument in its own index | HENRI
	int		is_label;		// HENRI
	int		byte_size;		//full size of every statement as bytes. 0 for labels | HENRI
	int		arg_1_size;		//is size of arg1 in bytes | HENRI
	int		arg_2_size;		//is size of arg2 in bytes | HENRI
	int		arg_3_size;		//is size of arg3 in bytes | HENRI
	int		arg_1_type;		//is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	int		arg_2_type;		//is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI
	int		arg_3_type;		// is NULL for none, 1 for T_REG, 2 for T_DIR and 3 for T_IND | HENRI

	char	*statement_code;		//statement code in hexadecimal | OTTO
	char	*argument_type_code;	//argument type code in hexadecimal | OTTO
	char	*arg_1_hex;				//arg 1 code in hexadecimal | OTTO
	char	*arg_2_hex;				//arg 2 code in hexadecimal | OTTO
	char	*arg_3_hex;				//arg 3 code in hexadecimal | OTTO
	char	*final;					//final bytecode for current statement | OTTO
}	t_input;

#endif