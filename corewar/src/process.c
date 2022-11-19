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

static void init_process_registries(int32_t *registeries, int i)
{
	int n;

	registeries[0] = -i;
	n = 1;
	while (n < REG_NUMBER)
		registeries[n++] = 0;
}

static void init_process(t_data *data, t_process *temp, int i)
{
	temp->id = i;
	temp->carry = false;
	//code pointer
	temp->cursor = data->champions[i - 1]->start_addr;
	//printf("cursor: %d\n", data->champions[i - 1]->start_addr);
	//last live  statement?
	//cycles_remaining;
	//byte_jump_size

	init_process_registries(temp->registeries, i);
}

static void add_process(t_data *data, t_process **head, int i)
{
	t_process *temp;

	temp = malloc(sizeof(t_process));
	if (!temp)
		error(NULL, "Allocation failed in add_process", 0);

	if (*head == NULL)
		temp->next = NULL;
	else
		temp->next = *head;
	init_process(data, temp, i);
	*head = temp;
}

void create_processes(t_data *data, t_process **head)
{
	int i;

	i = 1;
	printf("champs_num-> %d\n", data->champions_num);
	while (i <= data->champions_num)
	{
		//malloc process and add to list
		add_process(data, head, i);
		i++;
	}
}
