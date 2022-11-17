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

int	is_direct_label(char *current)
{
	int	i;

	i = 0;
	while (current[i])
	{
		if (current[i] == '%')
		{
			if (current[i + 1] == ':')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

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
char	*make_dir_hex(t_input *data, int current, int current_pos)
{
	int	dir_num;
	int	i;

	dir_num = 0;
	i = 0;
	if (is_label(data->arg[current]))
	{
		if(current_label_is_defined(data->arg[current]))
		{
			/**/
		}
		else
		{
			dir_num = find_label_address(data, data->arg[current]);
			data->arg_hex[current] = ft_itoa_base(dir_num, 16);
		}
	}
	else
	{
		while (!ft_isnum(data->arg[current][i]))
			i++;
		dir_num = ft_atoi(&data->arg[current][i]);
		data->arg_hex[current] = ft_itoa_base(dir_num, 16);
	}
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
	int	i;
	int	reg_num;

	i = 0;
	reg_num = 0;
	while (!ft_isnum(data->arg[current][i]))
		i++;
	reg_num = ft_atoi(&data->arg[current][i]);
	data->arg_hex[current] = ft_itoa_base(reg_num, 16);
}

int	is_indirect_label(char *current)
{
	int	i;

	i = 0;
	while (current[i])
	{
		if (current[i] == ':')
			return (1);
		i++;
	}
	return (0);
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
char	*make_ind_hex(t_input *data, int current, int current_pos)
{
	int	ind_num;
	int	i;

	ind_num = 0;
	i = 0;
	if (is_indirect_label(data->arg[current]))
	{
		
	}
	else
	{
		while (!ft_isnum(data->arg[current][i]))
			i++;
		ind_num = ft_atoi(data->arg[current][i]);
		data->arg_hex[current] = ft_itoa_base(ind_num, 16);
	}
}

/*
function to find the different argument codes and fill them in the struct.
1 = T_REG
2 = T_DIR
3 = T_IND
*/
void	find_argument_codes(t_input *data, int current_pos)
{
	int	i;

	i = 1;
	while (data->arg[i])
	{
		if (data->arg_type[i] == 1)
			make_reg_hex(data, i);
		if (data->arg_type[i] == 2)
			make_dir_hex(data, i, current_pos);
		if (data->arg_type[i] == 3)
			make_ind_hex(data, i, current_pos);
		i++;
	}
}
