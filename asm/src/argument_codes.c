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
char	*make_dir_hex(t_input *data, int current)
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
void	make_reg_hex(t_input *data, int current)
{
	char	*current_arg;
	int		reg_num;

	if (current == 0)
		current_arg = data->arg_1;
	else if (current == 1)
		current_arg = data->arg_2;
	else if (current = 2)
		current_arg = data->arg_3;
	else
		return ;
	reg_num = ft_atoi(&current_arg[1]);
	if (current == 0)
		data->arg_1_hex = ft_itoa_base(reg_num, 16);
	else if (current == 1)
		data->arg_2_hex = ft_itoa_base(reg_num, 16);
	else
		data->arg_3_hex = ft_itoa_base(reg_num, 16)
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
char	*make_ind_hex(t_input *data, int current)
{
	/**/
}

/*
function to find the different argument codes and fill them in the struct.
1 = T_REG
2 = T_DIR
3 = T_IND
*/
void	find_argument_codes(t_input *data)
{
	int	i;

	i = 0;
	while (data->arg_size[i])
	{
		if (data->arg_type[i] == 1)
			make_reg_hex(data, i);
		if (data->arg_type[i] == 2)
			make_dir_hex(data, i);
		if (data->arg_type[i] == 3)
			make_ind_hex(data, i);
		i++;
	}
}
