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

static void	init_vectors(t_data *s_data)
{
	s_data->vec_input = (t_vec *)malloc(sizeof(t_vec));
	s_data->vec_tokens = (t_vec *)malloc(sizeof(t_vec));
	if (!s_data->vec_tokens || !s_data->vec_input)
		error(MALLOC_ERR);
	vec_new_arr(s_data->vec_input, 2);
	vec_new_arr(s_data->vec_tokens, 2);
}

/*
	Initializes whole t_data struct.
*/
void	init(t_data *data, t_header *header, t_error_log *error_log)
{
	header->magic = COREWAR_EXEC_MAGIC;
	ft_bzero(header->prog_name, PROG_NAME_LENGTH);
	header->prog_size = 0;
	ft_bzero(header->comment, COMMENT_LENGTH);
	header->comment_saved = false;
	header->name_saved = false;
	error_log->line = 1;
	error_log->column = 1;
	data->vec_input = NULL;
	data->s_header = header;
	data->s_error_log = error_log;
	data->champ_size = 0;
	init_vectors(data);
}

t_input	*init_values(t_input *element)
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
	element->total_size = 0;
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
	element->arg_count = 0;
	return (element);
}
