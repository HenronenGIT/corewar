/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 16:07:32 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

//make ft_pow return 1 in case of zero pow
static int32_t	read_bytes(t_data *data, int idx, int size)
{
	int32_t sum;
	int32_t byte;

	idx += 1;
	sum = 0;
	while (size)
	{
		byte = data->arena[idx - size];
		sum += byte * ((int32_t)ft_pow(16, size))
		size--;
	}
}

void	get_arg_values(t_process *cur_process, t_data *data, t_types *types)
{
	int	i;
	int	start;

	start = cur_process->cursor + 1;
	i = 0;
	while (i < types->num_args)
	{
		start += types->size_arg[i];
		cur_process->args[i] = read_bytes(start, types->size_arg[i]);
		i++;
	}
}
