/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 16:31:51 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/28 16:31:52 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Initializes all structs from the stack memory.
Then initializes pointers to those structs to t_data struct;
*/
void init_structs(t_data *data, t_header *header, t_error_log *error_log)
{
	header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	// s_header.prog_size = ;
	ft_bzero(header->comment, COMMENT_LENGTH);
	error_log->line = 1;
	error_log->column = 1;
	data->vec_input = NULL;
	data->s_header = header;
	data->s_error_log = error_log;
}

void init_vectors(t_data *s_data)
{
	s_data->vec_input = (t_vec *)malloc(sizeof(t_vec));
	s_data->vec_tokens = (t_vec *)malloc(sizeof(t_vec));
	if (!s_data->vec_tokens || !s_data->vec_input)
		error(MALLOC_ERR);
	vec_new_arr(s_data->vec_input, 2);
	vec_new_arr(s_data->vec_tokens, 2);
}

t_input *init_values(t_input *element)
{
	element->op_code = 0;
	element->args[0] = NULL;
	element->args[1] = NULL;
	element->args[2] = NULL;
	element->args[3] = NULL;
	element->arg_type[0] = 0;
	element->arg_type[1] = 0;
	element->arg_type[2] = 0;
	element->arg_type[3] = 0;
	element->label_name = NULL;
	element->byte_size = 0;
	element->arg_size[0] = 0;
	element->arg_size[1] = 0;
	element->arg_size[2] = 0;
	element->arg_size[3] = 0;
	element->current_bytes = 0;
	element->argument_type_code = 0;
	element->arg_values[0] = 0;
	element->arg_values[1] = 0;
	element->arg_values[2] = 0;
	element->arg_values[3] = 0;
	element->final = NULL;
	return (element);
}
