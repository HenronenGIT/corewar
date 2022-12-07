/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/06 17:11:23 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

bool	get_arg_values(int8_t *arena, t_types *types, t_process *cur_process)
{
	int		i;
	int		idx;
	int32_t	val;
	size_t	start;

	start = 0;
	i = 0;
	while (i < types->num_args)
	{
		val = bytes2int((uint8_t*)&arena[start], types->size_arg[i]);
		
		if (types->type_arg[i] == T_REG)
		{
			if (val < 1 || val > 16)
				return (false);
			//records only the number of the registry, the value found in the registry is calculated in the individual functions as needed
			types->val_arg[i] = val;
		}
		else if (types->type_arg[i] == T_DIR)
			types->val_arg[i] = val;
		else if (types->type_arg[i] == T_IND)
		{
			if (cur_process->statement_code != 2)
			{
				//lld
				if (cur_process->statement_code == 12)
					idx = circular_mem(cur_process->cursor, val);
				else
					idx = circular_mem(cur_process->cursor, (val % IDX_MOD));
				//value found at idr addr
				types->val_arg[i] = bytes2int((uint8_t *)&arena[idx], 4);
			}
			//st
			else 
				//types->val_arg[i] = val % IDX_MOD;
				types->val_arg[i] = val;
		}
		start += types->size_arg[i];
		i++;
	}
	return (true);
}
