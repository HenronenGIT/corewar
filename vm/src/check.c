/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 09:47:37 by akilk             #+#    #+#             */
/*   Updated: 2023/01/10 14:08:46 by wdonnell         ###   ########.fr       */
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

/*
** go over the list of processes. If found died, remove it
** and put list together
*/

static void	print_dead(t_data *data, t_process *curr)
{
	if (data->verbosity & 0x08)
	{
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n", \
			curr->id, \
			data->cycles_total - curr->last_live, \
			data->cycles_to_die);
	}
}

static	void	remove_died(t_data *data, t_process **head)
{
	t_process	*prev;
	t_process	*curr;
	t_process	*remove;

	prev = NULL;
	curr = *head;
	while (curr)
	{
		if (is_died(data, curr) && data->num_processes--)
		{
			print_dead(data, curr);
			remove = curr;
			curr = curr->next;
			if (*head == remove)
				*head = curr;
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

void	check(t_data *data, t_process **head)
{
	data->num_checks_performed++;
	remove_died(data, head);
	if (data->num_checks_performed == MAX_CHECKS
		|| data->num_live_statements >= NBR_LIVE)
	{
		data->cycles_to_die -= CYCLE_DELTA;
		if (data->verbosity & 0x02)
			ft_printf("Cycle to die is now %d\n", data->cycles_to_die);
		data->num_checks_performed = 0;
	}
	data->num_live_statements = 0;
	data->cycles_after_check = 0;
}
