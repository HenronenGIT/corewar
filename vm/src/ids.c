/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ids.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:02:47 by akilk             #+#    #+#             */
/*   Updated: 2023/01/10 14:09:20 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** -n number
** sets the number of the next player.
** If non-existent, the player will have the next available number
** in the order of the parameters.
** The last player will have the first process in the order of execution.
*/

bool	id_used(int id, t_data *data)
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

static void	sort_ids(t_champion **unlisted, t_champion **result, t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < data->champions_num)
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
			result[data->champions[i]->id - 1] = data->champions[i];
		i++;
	}
	sort_ids(unlisted, result, data);
}
