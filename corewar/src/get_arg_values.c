/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/14 21:21:03 by wdonnell         ###   ########.fr       */
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

/*
static int32_t	get_ind(int8_t *arena, t_process *process, int32_t	val)
{
	int		idx;

	if (process->statement_code != 2)
	{
		if (process->statement_code != 12)
		{
			idx = circular_mem(process->cursor, (val % IDX_MOD));
			return (bytes2int((uint8_t *)arena, idx, 4));
		}
		else
		{
			idx = circular_mem(process->cursor, val);
			return (bytes2int((uint8_t *)arena, idx, 2));
		}
	}
	else
		return (val);
}
*/
bool	get_arg_values(t_data *data, t_types *types, t_process *process)
{
	int		i;
	size_t start;
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

/*
bool	get_arg_values(int8_t *arena, size_t start, t_types *types, t_process *process)
{
	int		i;
	int		idx;
	int32_t	val;
	//size_t	start;

	//start = 0;
	i = 0;
	while (i < types->num_args)
	{
		//checked that reading 2 bytes returns correct val
		val = bytes2int((uint8_t*)arena, start, types->size_arg[i]);
		
		if (types->type_arg[i] == T_REG)
		{
			if (val < 1 || val > 16)
			{
				ft_printf("val is: %d ", val);
				return (false);
			}
				
			//records only the number of the registry, 
			//the value found in the registry is calculated in the individual functions as needed
			types->val_arg[i] = val;
		}
		else if (types->type_arg[i] == T_DIR)
			types->val_arg[i] = val;
		else if (types->type_arg[i] == T_IND)
		{
			if (process->statement_code != 2)
			{
				if (process->statement_code != 12)
				{
					idx = circular_mem(process->cursor, (val % IDX_MOD));
					types->val_arg[i] = bytes2int((uint8_t *)arena, idx, 4);
				}
				else //is lld
				{
					idx = circular_mem(process->cursor, val);
					//read 2 bytes bug make flag to activate
					types->val_arg[i] = bytes2int((uint8_t *)arena, idx, 2);
				}
			}
			else
				//arg is st ->return addr to write at
				types->val_arg[i] = val % IDX_MOD;
		}
		start += types->size_arg[i];
		i++;
	}
	return (true);
}
*/