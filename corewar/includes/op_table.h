/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:48:22 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 12:59:45 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TABLE_H
# define OP_TABLE_H

#include "corewar.h"

#define NUM_OPS 16

#define ARG1_MASK 0xC0 //11000000
#define ARG2_MASK 0x30 //00110000
#define ARG3_MASK 0xC //00001100

typedef struct s_types
{
	int	t_arg1;
	int	t_arg2;
	int	t_arg3;
	int	size_arg1;
	int	size_arg2;
	int	size_arg3;
	int size_t_dir;

}				t_types;

void	op_live(t_process *cur_process, t_data *data);
void	op_ld(t_process *cur_process, t_data *data);
void	op_st(t_process *cur_process, t_data *data);
void	op_add(t_process *cur_process, t_data *data);
void	op_sub(t_process *cur_process, t_data *data);
void	op_and(t_process *cur_process, t_data *data);
void	op_or(t_process *cur_process, t_data *data);
void	op_xor(t_process *cur_process, t_data *data);
void	op_zjmp(t_process *cur_process, t_data *data);
void	op_ldi(t_process *cur_process, t_data *data);
void	op_sti(t_process *cur_process, t_data *data);
void	op_fork(t_process *cur_process, t_data *data);
void	op_lld(t_process *cur_process, t_data *data);
void	op_lldi(t_process *cur_process, t_data *data);
void	op_lfork(t_process *cur_process, t_data *data);
void	op_aff(t_process *cur_process, t_data *data);

typedef void (*t_op)(t_process *cur_process, t_data *data);

static const t_op g_dispatch[NUM_OPS] = {
	op_live,
	op_ld,
	op_st,
	op_add,
	op_sub,
	op_and,
	op_or,
	op_xor,
	op_zjmp,
	op_ldi,
	op_sti,
	op_fork,
	op_lld,
	op_lldi,
	op_lfork,
	op_aff
};

void	get_types(int8_t byte, t_types *types);

#endif