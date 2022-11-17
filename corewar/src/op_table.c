/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:58 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 15:20:05 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

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
	printf("XXXXX");
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

void	op_sti(t_process *cur_process, t_data *data)
{
	int8_t val_to_be_copied;
	int sum;
	t_types types;
	int num_args = 3;

	//comment stuff probably part of verbose mode
	ft_printf("process %d is on sti\n", cur_process->id);
	//get arg types and sizes
	types.size_t_dir = 2;
	types.num_args = 3;
	get_types(data->arena[cur_process->cursor + 1], &types);
	//tester
	//print_arg_types(&types);
	get_arg_values(cur_process, data, &types);
	//arg1
	val_to_be_copied = cur_process->args[0];




	//write val_to_be_copied (first param) to address: cursor + ((arg2 + arg3) % IDX_MOD)
	
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
