/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:58 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/24 12:26:37 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

/*
//tester stuff
static void print_arg_types(t_types *types)
{
	printf("T_REG = 1\nT_DIR = 2\nT_IND = 4\n");
	printf("t_arg1: %d\n", types->type_arg[0]);
	printf("sizeof arg1: %d\n", types->size_arg[0]);
	printf("t_arg2: %d\n", types->type_arg[1]);
	printf("sizeof arg2: %d\n", types->size_arg[1]);
	printf("t_arg3: %d\n", types->type_arg[2]);
	printf("sizeof arg3: %d\n", types->size_arg[2]);
}
*/
static void print_arg_values(t_types *types)
{
	int i = 0;

	while (i < 3)
	{
		ft_printf("arg %d val: %d\n", i + 1, types->val_arg[i]);
		i++;
	}
}
	//inside functions
	//set cycles remaing to -1
	//set byte jump size


void	op_live(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_ld(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_st(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_add(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_sub(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_and(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t val;
	
	
	ft_printf("process %d is on --> and\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 3;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[2] == T_REG && !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			val = (int32_t)(types.val_arg[0] & types.val_arg[1]);
			if (val)
				cur_process->carry = false;
			else
				cur_process->carry = true;
			ft_memcpy(cur_process->registeries[types.val_arg[2] - 1], val, 4);
			ft_printf("executed and -wrote %d to regristry %d\n", val, types.val_arg[2]);
		}
	}
	cur_process->cycles_remaining = -1;

}

void	op_or(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_xor(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_zjmp(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_ldi(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}


void	op_sti(t_process *cur_process, t_data *data)
{
	t_types types;
	int change;
	int idx;
	
	//comment stuff probably part of verbose mode
	ft_printf("process %d is on sti\n", cur_process->id);
	types.size_t_dir = 2;
	types.num_args = 3;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	//the 'true' for arg type code may not be needed
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[0] == T_REG && types.type_arg[2] != T_IND \
	&& !check_null(&types))
	{
		//correct args execute funtion
		//set start depending on if argument code is 2nd byte, or first byte
		//get_arg_values checks if the passed register(if exists) is correct
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			change = (types.val_arg[1] + types.val_arg[2]) % IDX_MOD;
			idx = circular_mem(cur_process->cursor, change);
			//chamge the size to types
			ft_memcpy(&data->arena[idx], &cur_process->registeries[types.val_arg[0] - 1], 1);
			//replacced with ft_memcpy
			//data->arena[idx] = types.val_arg[0];
			ft_printf("executed sti----\nwrote %#.2x to pos: %d\n", cur_process->registeries[types.val_arg[0] - 1], idx);
		}
	}
	cur_process->cycles_remaining = -1;
}

void	op_fork(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_lld(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_lldi(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_lfork(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_aff(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}
