/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg_values.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:02:39 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/23 14:43:36 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

void	get_arg_values(int8_t *arena, t_types *types)
{
	int	i;
	size_t start;

	start = 0;
	i = 0;
	while (i < types->num_args)
	{
		types->val_arg[i] = bytes2int((uint8_t*)&arena[start], types->size_arg[i]);
		start += types->size_arg[i];
		i++;
	}
}