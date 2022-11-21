/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:47:37 by akilk             #+#    #+#             */
/*   Updated: 2022/11/21 09:56:59 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static bool	is_died(t_data *data, t_process *process)
{
	if (data->cycles_to_die <= 0 \
		|| data->cycles_passed - process->last_live \
		>= data->cycles_to_die)
		return (true);
	return (false);
}

/* go over the list of processes. If found died, remove it
		and put list together  */
static	void	remove_died(t_data *data, t_process *head)
{
	t_process	*prev;
	t_process	*curr;
	t_process	*remove;

	prev = NULL;
	curr = head;
	while (curr)
	{
		if (is_died(data, curr))
		{
			ft_printf("%d is died\n", curr->id);
			remove = curr;
			data->cursors_num--;
			curr = curr->next;
			if (head == remove)
				head = curr;
			if (prev)
				prev->next = curr;
			ft_memdel((void **)&remove);
		}
		else
		{
			prev = curr;
			curr = curr->next;
		}
	}
}

static void	reset_live_statements(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->champions_num)
	{
		data->champions[i]->prev_live_statements \
		= data->champions[i]->curr_live_statements;
		data->champions[i]->curr_live_statements = 0;
		i++;
	}
	data->num_live_statements = 0;
}

void	check(t_data *data, t_process *head)
{
	data->num_checks_performed++;
	remove_died(data, head);
	if (data->num_checks_performed == MAX_CHECKS || data->num_live_statements >= NBR_LIVE)
	{
		data->cycles_to_die -= CYCLE_DELTA;
		data->num_checks_performed = 0;
	}
	reset_live_statements(data);
	data->cycles_after_check = 0;
}
