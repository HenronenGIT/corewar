/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:47 by akilk             #+#    #+#             */
/*   Updated: 2022/11/10 14:18:01 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	parse_dump_flag(int *argc, char ***argv, t_vm *vm)
{
	if (!vm->dump_print_mode && *argc >= 2 && ft_isint(*(*argv + 1), true))
	{
		if ((vm->dump_cycle = ft_atoi(*(*argv + 1))) < 0)
			vm->dump_cycle = -1;
		if (!ft_strcmp(**argv, "-d"))
			vm->dump_print_mode = 64;
		else
			vm->dump_print_mode = 32;
		(*argc) -= 2;
		(*argv) += 2;
	}
	else
		print_help();
}

void	parse_dump(t_data *data)
{
	if (data->)
}

void		print_arena(uint8_t *arena, int print_mode)
{
	int	i;
	int	j;

	i = 0;
	while (i < MEM_SIZE)
	{
		ft_printf("%.4p : ", i);
		j = 0;
		while (j < print_mode)
		{
			ft_printf("%.2x ", arena[i + j]);
			j++;
		}
		ft_printf("\n");
		i += print_mode;
	}
}