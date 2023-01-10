/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2023/01/10 14:29:52 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

/*
** if statement code is 3 'st' (2) return val of arg as address
** if code is not 13 'lld' read val at address
** if code is 'lld' do not truncate address by modulo
** and read only 2 bytes at address to duplicate original vm bug
*/

static int32_t	get_ind(t_data *data, t_process *process, int32_t	val)
{
	int		idx;

	if (process->statement_code != 2)
	{
		if (process->statement_code != 12)
			idx = circular_mem(process->cursor, (val % IDX_MOD));
		else
		{
			idx = circular_mem(process->cursor, val);
			if (data->verbosity & 0x01)
				return (bytes2int((uint8_t *)data->arena, idx, 2));
		}
		return (bytes2int((uint8_t *)data->arena, idx, 4));
	}
	else
		return (val);
}

bool	get_arg_values(t_data *data, t_types *types, t_process *process)
{
	int		i;
	size_t	start;
	int32_t	val;

	start = (process->cursor + 2) % MEM_SIZE;
	i = 0;
	while (i < types->num_args)
	{
		val = bytes2int((uint8_t *)data->arena, start, types->size_arg[i]);
		if (types->type_arg[i] == T_REG)
		{
			if (val < 1 || val > 16)
				return (false);
			types->val_arg[i] = val;
		}
		else if (types->type_arg[i] == T_DIR)
			types->val_arg[i] = val;
		else if (types->type_arg[i] == T_IND)
			types->val_arg[i] = get_ind(data, process, val);
		start += types->size_arg[i];
		start %= MEM_SIZE;
		i++;
	}
	return (true);
}
