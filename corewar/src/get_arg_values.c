/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/24 12:26:38 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

bool	get_arg_values(int8_t *arena, t_types *types, t_process *cur_process)
{
	int		i;
	int		val;
	size_t	start;

	start = 0;
	i = 0;
	while (i < types->num_args)
	{
		//types->val_arg[i] = bytes2int((uint8_t*)&arena[start], types->size_arg[i]);
		val = bytes2int((uint8_t*)&arena[start], types->size_arg[i]);
		if (types->type_arg[i] == T_REG)
		{
			//check regies
			if (val < 1 || val > 16)
				return (false);
			//also is reg 1 as argument, the same as reg 0?
			types->val_arg[i] = (int32_t)cur_process->registeries[val - 1];
		}
		else if (types->type_arg[i] == T_DIR)
			types->val_arg[i] = val;
		else if (types->type_arg[i] == T_IND)
			types->val_arg[i] = circular_mem(cur_process->cursor, (val % IDX_MOD));
		start += types->size_arg[i];
		i++;
	}
	return (true);
}
