/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 12:47:39 by okoponen          #+#    #+#             */
/*   Updated: 2023/01/10 11:03:05 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
	print all information from all structs
*/
static void	print_stmnt(t_stmnt *data, int fd)
{
	int	i;
	int	temp;

	i = 0;
	temp = 0;
	write(fd, &data->op_code, 1);
	if (data->argument_type_code)
		write(fd, &data->argument_type_code, 1);
	while (data->arg_size[i])
	{	
		if (data->arg_size[i] == 1)
			temp = data->arg_values[i];
		else
			temp = int_to_bigendian(data->arg_values[i], data->arg_size[i]);
		write(fd, &temp, data->arg_size[i]);
		i++;
	}

}

/*
	find numeric value in T_DIR, T_REG or T_IND type argument when argument 
	also has characters (r or &)
*/
int	find_number(char *current_arg)
{
	int	i;

	i = 0;
	if (current_arg[0] == '%' || current_arg[0] == 'r')
		i++;
	return (ft_atoi(&current_arg[i]));
}

/*
	save values in int form for all arguments
*/
void	save_argument_values(t_stmnt **original_data, t_stmnt *data, \
							int current_arg, int curr_struct)
{
	if (is_label_call(data->args[current_arg]))
		find_label_addr(original_data, data->args[current_arg], current_arg, \
		curr_struct);
	else
		data->arg_values[current_arg] = find_number(data->args[current_arg]);
}

/*
	generate input value for argument type code and for different arguments of a
	single statement
*/
void	generate_input(t_stmnt **original_data, t_stmnt *data, int curr_struct)
{
	int	i;

	i = 0;
	if (g_op_tab[data->op_code - 1].arg_type_code != 0)
		save_atc(data);
	while (data->args[i])
	{
		save_argument_values(original_data, data, i, curr_struct);
		i++;
	}
}

/*
	loop through all statements and labels and generate input for each
	statement, skipping labels
*/
void	generate_bytecode(t_vec *vec_input, int fd)
{
	int		i;
	t_stmnt	**data;

	i = 0;
	data = (t_stmnt **)vec_input->array;
	while (data[i])
	{
		if (!data[i]->label_name)
		{
			generate_input(data, data[i], i);
			print_stmnt(data[i], fd);
		}
		i++;
	}
}
