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

void	save_atc(t_input *data)
{
	int		i;
	char	*temp;
	int		j;
	
	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * 9);
	if (!temp)
		exit(1);
	temp[8] = '\0';
	while (j < 9)
	{
		if (data->arg_type[i] == 1)
		{
			temp[j++] = '0';
			temp[j++] = '1';
		}
		else if (data->arg_type[i] == 2)
		{
			temp[j++] = '1';
			temp[j++] = '0';
		}
		else if (data->arg_type[i] == 3)
		{
			temp[j++] = '1';
			temp[j++] = '1';
		}
		else if (data->arg_type[i] == 0)
		{
			temp[j++] = '0';
			temp[j++] = '0';
		}
		i++;
	}
	data->argument_type_code = ft_btoi(temp);
	free(temp);
}

int	find_number(char *current_arg)
{
	int	i;

	i = 0;
	if (current_arg[0] == '%' || current_arg[0] == 'r')
		i++;
	return (ft_atoi(&current_arg[i]));
}

int	is_label_call(char *current_arg)
{
	int	i;

	i = 0;
	while (current_arg[i])
	{
		if (current_arg[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

void	find_label_addr(t_input **data, char *current_arg, int curr_arg, int curr_struct)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (data[i]->is_label)
		{
			if (ft_strcmp(data[i]->label_name, current_arg))
			{
				data[curr_struct]->arg_values[curr_arg] = data[i]->current_bytes - data[curr_struct]->current_bytes;
				return ;
			}
		}
		i++;
	}
}

void	save_argument_values(t_input **original_data, t_input *data, int current_arg, int curr_struct)
{
	int	num;

	num = 0;
	if (is_label_call(data->args[current_arg]))
		find_label_addr(original_data, data->args[current_arg], current_arg, curr_struct);
	else
		data->arg_values[current_arg] = find_number(data->args[current_arg]);
}

void	generate_input(t_input **original_data, t_input *data, int curr_struct)
{
	int	i;

	i = 0;
	save_atc(data);
	while (data->args[i])
	{
		save_argument_values(original_data, data, i, curr_struct);
		i++;
	}
}



void	generator(t_input **data)
{
	int			i;

	i = 0;
	// while (data[i])
	// {
	// 	printf("dasdas");
	// 	if (!data[i]->is_label)
	// 		generate_input(data, data[i], i);
	// 	i++;
	// }
}

int main(void)
{
	printf("asdasda");
	t_input test;
	t_input **array;

	array = (t_input **)malloc(sizeof(t_input *) * 2);
// //st r1, r2
	test.statement = 3;
	test.is_label = 0;
	test.current_bytes = 0;
	test.label_name[0] = '\0';
	test.byte_size = 4;
	test.arg_size[0] = 1;
	test.arg_size[1] = 1;
	test.arg_size[2] = 0;
	test.arg_type[0] = 1;
	test.arg_type[1] = 1;
	test.arg_type[2] = 0;
	test.args[0][0] = 'r';
	test.args[0][1] = '1';
	test.args[0][2] = '\0';
	test.args[1][0] = 'r';
	test.args[1][1] = '2';
	test.args[1][2] = '\0';
	array[0] = &test;
	array[1] = NULL;
	generator(array);
	return (0);
}
