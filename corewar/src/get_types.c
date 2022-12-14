/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:55:05 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/14 21:54:04 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

static void	get_arg1(int8_t byte, t_types *types)
{
	if ((byte & ARG1_MASK) == 0x40)
	{
		types->type_arg[0] = T_REG;
		types->size_arg[0] = 1;
	}
	else if ((byte & ARG1_MASK) == 0x80)
	{
		types->type_arg[0] = T_DIR;
		types->size_arg[0] = types->size_t_dir;
	}
	else if ((byte & ARG1_MASK) == 0xC0)
	{
		types->type_arg[0] = T_IND;
		types->size_arg[0] = 2;
	}
	else
	{
		types->type_arg[0] = T_NULL;
		types->size_arg[0] = 0;
	}
}

static void	get_arg2(int8_t byte, t_types *types)
{
	if ((byte & ARG2_MASK) == 0x10)
	{
		types->type_arg[1] = T_REG;
		types->size_arg[1] = 1;
	}
	else if ((byte & ARG2_MASK) == 0x20)
	{
		types->type_arg[1] = T_DIR;
		types->size_arg[1] = types->size_t_dir;
	}
	else if ((byte & ARG2_MASK) == 0x30)
	{
		types->type_arg[1] = T_IND;
		types->size_arg[1] = 2;
	}
	else
	{
		types->type_arg[1] = T_NULL;
		types->size_arg[1] = 0;
	}
}

static void	get_arg3(int8_t byte, t_types *types)
{
	if ((byte & ARG3_MASK) == 0x4)
	{
		types->type_arg[2] = T_REG;
		types->size_arg[2] = 1;
	}
	else if ((byte & ARG3_MASK) == 0x8)
	{
		types->type_arg[2] = T_DIR;
		types->size_arg[2] = types->size_t_dir;
	}
	else if ((byte & ARG3_MASK) == 0xC)
	{
		types->type_arg[2] = T_IND;
		types->size_arg[2] = 2;
	}
	else
	{
		types->type_arg[2] = T_NULL;
		types->size_arg[2] = 0;
	}
}

void	get_types(t_data *data, t_process *process, t_types *types)
{
	int8_t	byte;

	byte = data->arena[(process->cursor + 1) % MEM_SIZE];
	get_arg1(byte, types);
	get_arg2(byte, types);
	if (types->num_args == 3)
		get_arg3(byte, types);
	process->byte_jump_size = jump_size(types);
}
