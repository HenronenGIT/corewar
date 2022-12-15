/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/12/14 20:51:59 by wdonnell         ###   ########.fr       */
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
	int	num;

	if (*ac > 2 && valid_int(*(*av + 1)))
	{
		num = ft_atoi(*(*av + 1));
		data->dump_cycle = num;
		(*ac) -= 2;
		(*av) += 2;
	}
	else
		error(NULL, "Error in parse_dump()", 1);
}

/*
** verbosity 1 -> mimic supplied vm
** verbosity 2 -> show cycles
** verbosity 4 -> show operations
** verbosity 8 -> show deaths
** verbosity 16 -> show cursor movements
*/

void	parse_verbosity(int *ac, char ***av, t_data *data)
{
	int	num;

	if (*ac > 2 && valid_int(*(*av + 1)))
	{
		num = ft_atoi(*(*av + 1));
		data->verbosity = num;
		(*ac) -= 2;
		(*av) += 2;
	}
	else
		error(NULL, "Error in parse_verbosity()", 1);
}

void	parse(int ac, char **av, t_data *data)
{
	t_champion	*champion;

	av++;
	while (ac > 1)
	{
		if (!ft_strcmp(*av, "-dump"))
			parse_dump(&ac, &av, data);
		else if (is_cor_file(*av) || !ft_strcmp(*av, "-n"))
		{
			champion = init_champion();
			parse_n(&ac, &av, data, champion);
		}
		else if (!ft_strcmp(*av, "-v"))
			parse_verbosity(&ac, &av, data);
		else
			error(NULL, "Error in parse()", 1);
	}
	if (data->champions_num < 1 || data->champions_num > MAX_PLAYERS)
		error(NULL, "Champions amount should be between 1 and 4", 0);
	reset_ids(data);
	data->last_alive_champ = data->champions_num;
}
