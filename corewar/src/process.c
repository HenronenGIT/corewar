/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:55:35 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 16:09:21 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void	add_process(t_data *data, t_process **head, int i)
{
	t_process	*temp;

	temp = malloc(sizeof(t_process));
	if (!temp)
		error(NULL, "Allocation failed in add_process", 0);
	if (*head == NULL)
		temp->next = NULL;
	else
		temp->next = *head;
	if (!data->cycles_total)
		init_process(data, temp, i);
	else
		init_fork(data, temp, i);
	*head = temp;
}

void	create_processes(t_data *data)
{
	int			i;
	t_process	**head;

	head = &data->head;
	i = 1;
	while (i <= data->champions_num)
	{
		add_process(data, head, i);
		data->num_processes++;
		i++;
	}
	data->new_process_id = data->num_processes;
}
