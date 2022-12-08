/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/08 21:49:24 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

bool	get_arg_values(int8_t *arena, size_t start, t_types *types, t_process *cur_process)
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
			if (cur_process->statement_code != 2)
			{
				if (cur_process->statement_code != 12)
				{
					idx = circular_mem(cur_process->cursor, (val % IDX_MOD));
					types->val_arg[i] = bytes2int((uint8_t *)arena, idx, 4);
				}
				else //is lld
				{
					idx = circular_mem(cur_process->cursor, val);
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
