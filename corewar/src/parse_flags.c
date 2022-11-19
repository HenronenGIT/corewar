/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:47 by akilk             #+#    #+#             */
/*   Updated: 2022/11/19 18:41:34 by akilk            ###   ########.fr       */
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
static bool	valid_int(char *str)
{
	int	i;
	double	num;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (false);
		i++;
	}
	num = ft_atol(str);
	if (num < 0 || num > INT_MAX)
		return (false);
	return (true);
}

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
** -n number
** sets the number of the next player.
** If non-existent, the player will have the next available number
** in the order of the parameters.
** The last player will have the first process in the order of execution.
*/

static bool	id_used(int id, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->champions_num)
	{
		if (id == data->champions[i]->id)
			return (true);
		i++;
	}
	return (false);
}

void	parse_n(int *ac, char ***av, t_data *data, t_champion *champion)
{
	int		num;
	char	*name;

	if (*ac > 3 && !ft_strcmp(**av, "-n"))
	{
		num = ft_atoi(*(*av + 1));
		name = *(*av + 2);
		if (num < 1 || num > MAX_PLAYERS || !is_cor_file(name) \
				|| id_used(num, data))
			error(NULL, "Error in parse_n()", 1);
		champion->id = num;
		parse_champions(name, champion);
		(*ac) -= 3;
		(*av) += 3;
	}
	else if (is_cor_file(**av))
	{
		parse_champions(**av, champion);
		(*ac)--;
		(*av)++;
	}
	else
		error(NULL, "Error in parse_n()", 1);
	data->champions_num++;
	data->champions[data->champions_num - 1] = champion;
}

static void	sort_ids(t_champion **unlisted, t_champion **result, t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (unlisted[k] != NULL && i < data->champions_num)
	{
		if (result[i] == NULL)
		{
			result[i] = unlisted[k++];
			result[i]->id = i + 1;
		}
		i++;
	}
	i = -1;
	while (++i < data->champions_num)
		data->champions[i] = result[i];
}

void	reset_ids(t_data *data)
{
	int			i;
	int			k;
	t_champion	*unlisted[MAX_PLAYERS];
	t_champion	*result[MAX_PLAYERS];

	i = 0;
	k = 0;
	ft_bzero(result, sizeof(result));
	ft_bzero(unlisted, sizeof(unlisted));
	while (i < data->champions_num)
	{
		if (data->champions[i]->id > data->champions_num)
			error(NULL, "champion's number is not correct", 1);
		else if (data->champions[i]->id == 0)
			unlisted[k++] = data->champions[i];
		else
			result[data->champions[i]->id - 1] =  data->champions[i];
		i++;
	}
	sort_ids(unlisted, result, data);
}
