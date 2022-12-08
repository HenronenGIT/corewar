/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:40:26 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/08 15:57:21 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

int	circular_mem(int pos, int change)
{
	if (pos + change < 0)
		return (MEM_SIZE + (pos + change));
	else
		return ((pos + change) % MEM_SIZE);
}

size_t	jump_size(t_types *types)
{
	size_t	n;
	int	i;

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

//fix with IDX_MOD
void	write_arena(int8_t *arena, int32_t *reg)
{
	int		i;
	int8_t	*p;

	p = (int8_t *)reg;
	arena += 3;
	i = 0;
	while (i++ < 4)
		*arena-- = *p++;
}

void	update_carry(t_process *cur_process, int32_t val)
{
	if (val)
		cur_process->carry = false;
	else
		cur_process->carry = true;
}

//maybe make verbosity_util.c??
void	print_byte_jumps(t_process *cur_process, t_data *data)
{
	int	idx;
	int	i;

	idx = cur_process->cursor;
	i = 0;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", cur_process->byte_jump_size, idx, idx + cur_process->byte_jump_size);
	while (i < cur_process->byte_jump_size)
	{
		ft_printf("%.2x ", (uint8_t)data->arena[(idx + i)]);
		i++;
	}
	//tester
	//ft_printf(" | P %d ", cur_process->id);
	ft_printf("\n");
}