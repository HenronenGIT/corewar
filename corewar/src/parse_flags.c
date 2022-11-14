/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:47 by akilk             #+#    #+#             */
/*   Updated: 2022/11/12 16:18:31 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
-dump nbr_cycles
at the end of nbr_cycles of executions, dump the memory
on the standard output and quit the game.
The memory must be dumped in the
hexadecimal format with 32 octets per line.
*/

void	parse_dump(int *ac, char ***av, t_data *data)
{
	int	i;

	i = 1;
	while (i <= MEM_SIZE)
	{
		printf("%.2x", data->arena[i]);
		if (i % 32 == 0)
			printf("\n");
		else
			printf(" ");
		i++;
	}
	(*ac) -= 2;
	(*av) += 2;
}
