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