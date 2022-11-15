/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:47:39 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/09 12:47:40 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Take all finalized individual hex codes and join them all into the final
hexcode string consisting of statement code, argument type code and 
the individual codes for all arguments. NULL values are skipped
*/
void	make_final_hex(t_input *data)
{

}

/*
Function to convert the binary version of the argument type code into
hexadecimal including 0x prefix.
*/
char	*conv_binary_to_hex(char *binary)
{

}

/*
Different argument types have defined binary codes that correspond to their
types. Here we join those codes together for every argument to create the
binary version of this argument type code.
Arguments of type T_DIR have the code 10
Arguments of type T_DIR have the code 01
Arguments of type T_DIR have the code 11
For no argument type we must still add code 00.
*/
char	*find_arg_type(int type, char *temp)
{
	if (!type)
		return (ft_strcat(temp, "00"));
	if (type = 1)
		return (ft_strcat(temp, "10"));
	if (type = 2)
		return (ft_strcat(temp, "01"));
	if (type = 3)
		return (ft_strcat(temp, "11"));
}

/*
Find the argument type for given instruction by combinging all values of the
argument types in a large string and then converting the final result into
hexadecimal
1 = T_DIR = 10, 2 = T_REG  = 01, 3 = T_IND 11
*/
void	find_atc(t_input *data)
{
	char	*temp;
	int		i;

	i = 0;
	temp = malloc(sizeof(char) * ((data->arg_size[0]) * 2 + (data->arg_size[1]) * 2 + (data->arg_size[2]) * 2 + 3));
	if (!temp)
		error(1, "malloc error in find_atc");
	while (data->arg_type[i])
		temp = find_arg_type(data->arg_type[i++], temp);
	temp = find_arg_type(0, temp);
	data->argument_type_code = conv_binary_to_hex(temp);
	free (temp);
}

/*
For the statement code we only need to convert statement code to
hexadecimal for final hexcode for this statement.
*/
void	find_statement_code(t_input *data)
{
	data->statement_code = ft_itoa_base(data->statement, 16);
	//make sure statement code is in format 0x00
}

/*
Function to generate all different hex codes and fill them in the struct.
*/
void	generate_code(t_input *data)
{
	find_statement_code(data);
	find_atc(data);
	find_argument_codes();
	make_final_hex(data);
}

/*
Initial function to parse through all statements and then join them
together to generate the final hexcode (opcode or bytecode) for all
statements in the array.
*/
void	generator(t_input **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!data[i]->is_label)
			generate_input(data[i]);
		i++;
	}
}
