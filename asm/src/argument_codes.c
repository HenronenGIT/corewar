/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argument_codes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 14:57:06 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/09 14:57:09 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Find argument codes for arguments of type T_DIR (direct)
Hex codes for direct type arguments are made differently depending
on if the given argument is a direct label or a direct number.
For direct numbers we only have to convert the number into hexadecimal and
make sure our answer has enough 0s determined by the size of the argument.
For direct labels we must first find out what is the address of that
given label and convert that number into hexadecimal and pad the number
with the correct ammount of 0s depending on the size of the given argument.
*/
char	*make_dir_hex(t_input *data, int curr, int curr_size)
{
	/**/
}

/*
find argument codes for arguments of type T_REG (registry)
Hex codes for registry type arguments are made by simply converting the
given registry number into hexadecimal and adding 0x prefix and making
sure we pad the number with the correct ammount of 0s depending on the
size of the given argument.
*/
char	*make_reg_hex(t_input *data, int curr, int curr_size)
{

}

/*
Find argument codes for arguments of type T_IND (indirect)
hex codes for indirect type arguments are made differently depending
on if the given argument is a indirect label or an indirect number.
Indirect numbers are just added as numbers converted into hexadecimal
and padding the value with the correct ammount of 0s depending on the 
size of the argument.
For indirect labels we need to find the relative address of the given label
and convert the "distance" into hexadecimal and of course pad the final
result with the correct ammount of 0s depending on the size of the arg.
*/
char	*make_ind_hex(t_input *data, int curr, int curr_size)
{
	/**/
}

/*
function to find the different argument codes and fill them in the struct
*/
char	*find_argument_codes(t_input *data, int curr_size, int curr_type, int curr)
{
	if (curr_arg_type)
	{
		if (curr_type == 1)
			return (make_dir_hex(data, curr, curr_size));
		if (curr_type == 2)
			return (make_reg_hex(data, curr, curr_size));
		if (curr_type == 3)
			return (make_ind_hex(data, curr, curr_size));
	}
	else
		return (NULL);
}
