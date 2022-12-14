/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:40:26 by wdonnell          #+#    #+#             */
/*   Updated: 2023/01/10 14:30:36 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

int	circular_mem(int pos, int change)
{
	if (pos + change < 0)
		return (MEM_SIZE + (pos + change) % MEM_SIZE);
	else
		return ((pos + change) % MEM_SIZE);
}

size_t	jump_size(t_types *types)
{
	size_t	n;
	int		i;

	n = 2;
	i = 0;
	while (i < types->num_args)
		n += types->size_arg[i++];
	return (n);
}

bool	check_null(t_types *types)
{
	int	num;

	num = types->num_args;
	while (--num)
	{
		if (types->type_arg[num] == T_NULL)
			return (true);
	}
	return (false);
}

void	write_arena(int8_t *arena, int idx, int32_t *reg)
{
	int		i;
	int8_t	*p;

	p = (int8_t *)reg;
	idx = (idx + 3) % MEM_SIZE;
	i = 0;
	while (i++ < 4)
	{
		arena[idx] = *p;
		idx = (idx - 1);
		if (idx < 0)
			idx = MEM_SIZE + idx;
		p++;
	}
}

void	update_carry(t_process *cur_process, int32_t val)
{
	if (val)
		cur_process->carry = false;
	else
		cur_process->carry = true;
}
