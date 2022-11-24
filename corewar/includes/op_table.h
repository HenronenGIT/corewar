/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:48:22 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/24 12:26:43 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TABLE_H
# define OP_TABLE_H

#include "corewar.h"

#define NUM_OPS 16

#define ARG1_MASK 0xC0 //11000000
#define ARG2_MASK 0x30 //00110000
#define ARG3_MASK 0xC //00001100

#define T_NULL 0 //use if type is undetermined

typedef struct s_types
{
	int type_arg[3];
	size_t size_arg[3];
	int32_t val_arg[3];
	size_t size_t_dir;
	int num_args;

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
bool	get_arg_values(int8_t *arena, t_types *types, t_process *cur_process);
/* op_util */
int		circular_mem(int pos, int change);
size_t	jump_size(t_types *types, bool arg_type_code);
bool	check_null(t_types *types);

#endif