/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 14:40:26 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/23 14:43:31 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

int circular_mem(int pos, int change)
{
	if (pos + change < 0)
		return (MEM_SIZE + (pos + change));
	else
		return ((pos + change) % MEM_SIZE);
}

size_t jump_size(t_types *types, bool arg_type_code)
{
	size_t n;
	int i;

	n = 0;
	if (arg_type_code)
		n++;
	i = 0;
	while (i < types->num_args)
		n += types->size_arg[i++];
	return (n);
}
