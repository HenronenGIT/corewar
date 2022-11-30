/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:47:37 by akilk             #+#    #+#             */
/*   Updated: 2022/11/30 16:38:11 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static bool	is_died(t_data *data, t_process *process)
{
	if (data->cycles_to_die <= 0 \
		|| data->cycles_total - process->last_live \
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
			data->num_processes--;
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
//can this be done in data and not champions??
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
