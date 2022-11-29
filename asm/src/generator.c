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

void save_atc(t_input *data)
{
	int i;
	char *temp;
	int j;

	i = 0;
	j = 0;
	temp = (char *)malloc(sizeof(char) * 9);
	if (!temp)
		exit(1);
	temp[8] = '\0';
	while (j < 8)
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

int find_number(char *current_arg)
{
	int i;

	i = 0;
	if (current_arg[0] == '%' || current_arg[0] == 'r')
		i++;
	return (ft_atoi(&current_arg[i]));
}

int is_label_call(char *current_arg)
{
	int i;

	i = 0;
	while (current_arg[i])
	{
		if (current_arg[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

void find_label_addr(t_input **data, char *current_arg, int curr_arg, int curr_struct)
{
	int i;

	i = 0;
	while (data[i])
	{
		if (data[i]->label_name)
		{
			if (ft_strcmp(data[i]->label_name, current_arg))
			{
				data[curr_struct]->arg_values[curr_arg] = data[i]->current_bytes - data[curr_struct]->current_bytes;
				return;
			}
		}
		i++;
	}
}

void save_argument_values(t_input **original_data, t_input *data, int current_arg, int curr_struct)
{
	int num;

	num = 0;
	if (is_label_call(data->args[current_arg]))
		find_label_addr(original_data, data->args[current_arg], current_arg, curr_struct);
	else
		data->arg_values[current_arg] = find_number(data->args[current_arg]);
}

void make_final(t_input *data)
{
	printf("%s%s%s%s%s\n", ft_itoh(data->op_code, 1), ft_itoh(data->argument_type_code, 1), ft_itoh(data->arg_values[0], data->arg_size[0]), ft_itoh(data->arg_values[1], data->arg_size[1]), ft_itoh(data->arg_values[2], data->arg_size[2]));
}

void generate_input(t_input **original_data, t_input *data, int curr_struct)
{
	int i;

	i = 0;
	save_atc(data);
	while (data->args[i])
	{
		save_argument_values(original_data, data, i, curr_struct);
		i++;
	}
	make_final(data);
}

void generator(t_input **data)
{
	int i;

	i = 0;
	while (data[i])
	{
		if (!data[i]->label_name)
			generate_input(data, data[i], i);
		i++;
	}
}

void print_array(t_input *data)
{
	printf("op_code: %d\n", data->op_code);
	printf("a1 size: %d\n", data->arg_size[0]);
	printf("a2 size: %d\n", data->arg_size[1]);
	printf("a3 size: %d\n", data->arg_size[2]);
	printf("a1 type: %d\n", data->arg_type[0]);
	printf("a2 type: %d\n", data->arg_type[1]);
	printf("a3 type: %d\n", data->arg_type[2]);
	printf("arg1: %s\n", data->args[0]);
	printf("arg2: %s\n", data->args[1]);
	printf("arg3: %s\n", data->args[2]);
	printf("atc: %d\n", data->argument_type_code);
	printf("arg1_value: %d\n", data->arg_values[0]);
	printf("arg2_value: %d\n", data->arg_values[1]);
	printf("arg3_value: %d\n", data->arg_values[2]);
}

int main(void)
{
	t_input test;
	t_input **array;

	array = (t_input **)malloc(sizeof(t_input *) * 2);

	// //and r1, %0, r1
	test.op_code = 6;
	test.current_bytes = 0;
	test.label_name[0] = '\0';
	test.byte_size = 8;
	test.arg_size[0] = 1;
	test.arg_size[1] = 4;
	test.arg_size[2] = 1;
	test.arg_type[0] = 1;
	test.arg_type[1] = 2;
	test.arg_type[2] = 1;
	test.args[0] = ft_strdup("r1");
	test.args[1] = ft_strdup("%0");
	test.args[2] = ft_strdup("r1");
	array[0] = &test;
	array[1] = NULL;
	generator(array);
	//	print_array(array[0]);
	return (0);
}