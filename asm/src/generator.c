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
//	data->argument_type_code = ft_btoi(temp);
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
				data[curr_struct]->arg_values[curr_arg] = data[i]->label_addr - data[curr_struct]->current_bytes;
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
	int			current_pos;

	i = 0;
	current_pos = 0;
	while (data[i])
	{
		data[i]->current_bytes = current_pos;
		if (!data[i]->is_label)
			generate_input(data, data[i], i);
		current_pos += data[i]->byte_size;
		i++;
	}
}

int main(void)
{
	t_input *data[1];

//st r1, r2
	data[0]->statement = 3;
	data[0]->is_label = 0;
	data[0]->label_addr = 0;
	data[0]->label_name[0] = '\0';
	data[0]->byte_size = 4;
	data[0]->arg_size[0] = 1;
	data[0]->arg_size[1] = 1;
	data[0]->arg_size[2] = 0;
	data[0]->arg_type[0] = 1;
	data[0]->arg_type[1] = 1;
	data[0]->arg_type[2] = 0;
	data[0]->args[0][0] = 'r';
	data[0]->args[0][1] = '1';
	data[0]->args[1][0] = 'r';
	data[0]->args[1][1] = '2';
	generator(data);
	return (0);
}
