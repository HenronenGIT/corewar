/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:58 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/02 13:40:51 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	op_live(t_process *cur_process, t_data *data)
{
	int player;

	cur_process->byte_jump_size = 5; //size of T_DIR + 1 
	//count process as alive??
	cur_process->last_live = data->cycles_total;
	//count arg as last_alive_champ. Later check if this is a valid champ?
	data->last_alive_champ = bytes2int((uint8_t *)&data->arena[cur_process->cursor + 1], 4);
	//are champ id's always negative??
	player = data->last_alive_champ * -1;
	if (player <= data->champions_num && player > 0)
		ft_printf("A process shows that player %d (%s) is alive\n", player, data->champions[player - 1]->name);
	//TESTING
	ft_printf("P%5d | live %d\n", cur_process->id, data->last_alive_champ);

}

void	op_ld(t_process *cur_process, t_data *data)
{
	t_types types;
	
	//ft_printf("process %d is on 'ld'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 2;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	cur_process->byte_jump_size = jump_size(&types, true);
	//check if args are of correct type
	if (types.type_arg[1] == T_REG && (types.type_arg[0] != T_REG && types.type_arg[0] != T_NULL))
	{
		//get values, checks if is a valid T_REG
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			cur_process->registeries[types.val_arg[1] - 1] = types.val_arg[0];
			
			if (types.val_arg[0])
				cur_process->carry = false;
			else
				cur_process->carry = true;
		}
	}
	ft_printf("P%5d | ld %d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1]);

}

void	op_st(t_process *cur_process, t_data *data)
{
	t_types types;
	
	ft_printf("process %d is on 'st'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 2;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[0] == T_REG && (types.type_arg[1] != T_DIR && types.type_arg[1] != T_NULL))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[1] == T_REG)
				cur_process->registeries[types.val_arg[0] - 1] = cur_process->registeries[types.val_arg[1] - 1];
			else
				cur_process->registeries[types.val_arg[0] - 1] = types.val_arg[1];
		}
	}
}

void	op_add(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t sum;

	types.size_t_dir = 4;
	types.num_args = 3;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	cur_process->byte_jump_size = jump_size(&types, true);
	//check if args are of correct type
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG && types.type_arg[2] == T_REG)
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			sum = cur_process->registeries[types.val_arg[0] - 1] + cur_process->registeries[types.val_arg[1] - 1];
			cur_process->registeries[types.val_arg[2] - 1] = sum;
			//ft_printf("val of sum in add: %d\n", sum);
			if (sum)
				cur_process->carry = false;
			else
				cur_process->carry = true;
		}
		ft_printf("P%5d | add r%d r%d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
	}
}

void	op_sub(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t diff;

	types.size_t_dir = 4;
	types.num_args = 3;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	cur_process->byte_jump_size = jump_size(&types, true);
	//check if args are of correct type
	if (types.type_arg[0] == T_REG && types.type_arg[1] == T_REG && types.type_arg[2] == T_REG)
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			//ft_printf("arg1: %d arg2: %d\n",cur_process->registeries[types.val_arg[0] - 1], cur_process->registeries[types.val_arg[1] - 1] );
			diff = cur_process->registeries[types.val_arg[0] - 1] - cur_process->registeries[types.val_arg[1] - 1];
			cur_process->registeries[types.val_arg[2] - 1] = diff;
			//ft_printf("val of diff in sub: %d\n", diff);

			if (diff)
				cur_process->carry = false;
			else
				cur_process->carry = true;
			ft_printf("P%5d | sub r%d r%d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
		
	}
}

void	op_and(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t val;
	
	
	//ft_printf("process %d is on 'and'\n", cur_process->id);
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
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] & types.val_arg[1]);
			if (val)
				cur_process->carry = false;
			else
				cur_process->carry = true;
			//cur_process->carry = val ^ 1;
			cur_process->registeries[types.val_arg[2] - 1] = val;
			//ft_memcpy(&cur_process->registeries[types.val_arg[2] - 1], &val, 4);
			//testinf ONLY
			ft_printf("P%5d | add %d %d r%d\n", cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2]);
		}
	}

}

void	op_or(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t val;
	
	ft_printf("process %d is on 'or'\n", cur_process->id);
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
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] | types.val_arg[1]);
			if (val)
				cur_process->carry = false;
			else
				cur_process->carry = true;
			//cur_process->carry = val ^ 1;
			cur_process->registeries[types.val_arg[2] - 1] = val;
			//ft_memcpy(&cur_process->registeries[types.val_arg[2] - 1], &val, 4);
			//testinf ONLY
			ft_printf("executed 'or' -wrote %d to regristry %d\n", val, types.val_arg[2]);

		}
	}
}

void	op_xor(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t val;
	
	ft_printf("process %d is on 'xor'\n", cur_process->id);
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
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			val = (int32_t)(types.val_arg[0] ^ types.val_arg[1]);
			if (val)
				cur_process->carry = false;
			else
				cur_process->carry = true;
			//cur_process->carry = val ^ 1;
			cur_process->registeries[types.val_arg[2] - 1] = val;
			//ft_memcpy(&cur_process->registeries[types.val_arg[2] - 1], &val, 4);
			//testinf ONLY
			ft_printf("executed 'xor' -wrote %d to regristry %d\n", val, types.val_arg[2]);

		}
	}
}

void	op_zjmp(t_process *cur_process, t_data *data)
{
	int	val;
	//ft_printf("CURSOR @: %d\n", cur_process->cursor);
	val = bytes2int((uint8_t *)&data->arena[cur_process->cursor + 1] , 2);
	if (cur_process->carry)
	{
		cur_process->cursor = circular_mem(cur_process->cursor, val);
		cur_process->byte_jump_size = 0;
	}
	else
		cur_process->byte_jump_size = 3; //size t_dir + 1
	//TESTING
	if (cur_process->carry)
		ft_printf("P%5d | zjmp %d OK\n", cur_process->id, val);
	else
		ft_printf("P%5d | zjmp %d FAILED\n", cur_process->id, val);
	
	
}

void	op_ldi(t_process *cur_process, t_data *data)
{
	t_types types;
	int change;
	int idx;
	
	//ft_printf("process %d is on 'ldi'\n", cur_process->id);
	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	//the 'true' for arg type code may not be needed
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[1] != T_IND && types.type_arg[2] == T_REG \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			change = (types.val_arg[0] + types.val_arg[1]) % IDX_MOD;
			idx = circular_mem(cur_process->cursor, change);
			
			//cur_process->registeries[types.val_arg[2] - 1] = bytes2int((uint8_t*)&data->arena[idx], 4);
			//OR
			ft_memcpy(&cur_process->registeries[types.val_arg[2] - 1], &data->arena[idx], 4);
			//testing
			ft_printf("P%5d | ldi %d %d r%d\n       | -> load from %d + %d = %d (with pc and mod %d)\n", \
			cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2], \
			types.val_arg[0], types.val_arg[1], types.val_arg[0] + types.val_arg[1], idx);
		}
		
	}
}


void	op_sti(t_process *cur_process, t_data *data)
{
	t_types types;
	int change;
	int idx;
	
	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[0] == T_REG && types.type_arg[2] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			if (types.type_arg[2] == T_REG)
				types.val_arg[2] = cur_process->registeries[types.val_arg[2] - 1];
			change = (types.val_arg[1] + types.val_arg[2]) % IDX_MOD;
			idx = circular_mem(cur_process->cursor, change);
			ft_memcpy(&data->arena[idx], &cur_process->registeries[types.val_arg[0] - 1], 4);

			//Testing
			ft_printf("P%5d | sti r%d %d %d\n       | -> store to %d + %d = %d (with pc and mod %d)\n", \
			cur_process->id, types.val_arg[0], types.val_arg[1], types.val_arg[2], \
			types.val_arg[1], types.val_arg[2], types.val_arg[1] + types.val_arg[2], idx);
			//tester
			//ft_printf("     ->wrote %d\n", cur_process->registeries[types.val_arg[0] - 1]);
		}
	}
}

void	op_fork(t_process *cur_process, t_data *data)
{
	//t_dir  2
	int idx;

	cur_process->byte_jump_size = 3; //size of T_DIR + 1
	idx = bytes2int((uint8_t *)&data->arena[cur_process->cursor + 1], 2) % IDX_MOD;
	data->new_cursor = circular_mem(cur_process->cursor, idx);
	//create new process at new_cursor
	data->parent = cur_process;
	add_process(data, &data->head, ++data->num_processes);
	//TESTING
	ft_printf("P%5d | fork %d (%d)\n", cur_process->id, idx, data->new_cursor);
}

void	op_lld(t_process *cur_process, t_data *data)
{
	t_types types;
	int32_t val;
	int idx;

	ft_printf("process %d is on 'lld'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 2;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	cur_process->byte_jump_size = jump_size(&types, true);
	//check if args are of correct type
	if (types.type_arg[1] == T_REG && (types.type_arg[0] != T_REG && types.type_arg[0] != T_NULL))
	{
		//get values, checks if is a valid T_REG
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			idx = circular_mem(cur_process->cursor, types.val_arg[0]);
			val = bytes2int((uint8_t*)&data->arena[idx], 4);
			cur_process->registeries[types.val_arg[1] - 1] = val;
			if (val)
				cur_process->carry = false;
			else
				cur_process->carry = true;
		}
			
	}
}

void	op_lldi(t_process *cur_process, t_data *data)
{
	t_types types;
	int change;
	int idx;
	
	//comment stuff probably part of verbose mode
	ft_printf("process %d is on 'lldi'\n", cur_process->id);
	types.size_t_dir = 2;
	types.num_args = 3;
	//only if arg type code is 2nd byte
	get_types(data->arena[cur_process->cursor + 1], &types);
	//set regardless if incorrect types
	//the 'true' for arg type code may not be needed
	cur_process->byte_jump_size = jump_size(&types, true);
	if (types.type_arg[2] == T_REG && types.type_arg[1] != T_IND \
	&& !check_null(&types))
	{
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
		{
			if (types.type_arg[0] == T_REG)
				types.val_arg[0] = cur_process->registeries[types.val_arg[0] - 1];
			if (types.type_arg[1] == T_REG)
				types.val_arg[1] = cur_process->registeries[types.val_arg[1] - 1];
			change = types.val_arg[0] + types.val_arg[1];
			idx = circular_mem(cur_process->cursor, change);
			
			//cur_process->registeries[types.val_arg[2] - 1] = bytes2int((uint8_t*)&data->arena[idx], 4);
			//OR
			ft_memcpy(&cur_process->registeries[types.val_arg[2] - 1], &data->arena[idx], 4);

			//modify carry
			if (cur_process->registeries[types.val_arg[2] - 1])
				cur_process->carry = false;
			else
				cur_process->carry = true;
		}
	}
}

void	op_lfork(t_process *cur_process, t_data *data)
{
	printf("XXXXX");
}

void	op_aff(t_process *cur_process, t_data *data)
{
	
	t_types types;
	
	//comment stuff probably part of verbose mode
	ft_printf("process %d is on 'aff'\n", cur_process->id);
	types.size_t_dir = 4;
	types.num_args = 1;
	//sc + atc + 4
	get_types(data->arena[cur_process->cursor + 1], &types);
	//hardcoded in this case
	cur_process->byte_jump_size = 6;
	if (types.type_arg[0] == T_REG)
		if (get_arg_values(&data->arena[cur_process->cursor + 2], &types, cur_process))
			ft_printf("AFF: %c\n", (char)cur_process->registeries[types.val_arg[0] - 1]);

}
