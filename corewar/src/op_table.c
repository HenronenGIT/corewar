/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:42:58 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 12:58:06 by wdonnell         ###   ########.fr       */
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
	printf("t_arg1: %d\n", types->t_arg1);
	printf("sizeof arg1: %d\n", types->size_arg1);
	printf("t_arg2: %d\n", types->t_arg2);
	printf("sizeof arg2: %d\n", types->size_arg2);
	printf("t_arg3: %d\n", types->t_arg3);
	printf("sizeof arg3: %d\n", types->size_arg3);
}

void	op_sti(t_process *cur_process, t_data *data)
{
	int8_t val_to_be_copied;
	int16_t val2;
	int16_t val3;
	t_types types;
	int num_args = 3;

	//comment stuff
	ft_printf("process %d is on sti\n", cur_process->id);
	//get arg types and sizes
	types.size_t_dir = 2;
	printf("types byte %.2x\n", data->arena[cur_process->cursor + 1]);
	get_types(data->arena[cur_process->cursor + 1], &types);
	val_to_be_copied = data->arena[cur_process->cursor + 2];
	//tester
	print_arg_types(&types);



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
