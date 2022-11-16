/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_table.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:48:22 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/16 14:29:29 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_TABLE_H
# define OP_TABLE_H

#include "corewar.h"

#define NUM_OPS 16

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

#endif