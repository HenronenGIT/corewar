/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:55:35 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 15:08:16 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static void init_carriage_registries(int32_t *registeries, int i)
{
	int n;

	registeries[0] = -i;
	n = 1;
	while (n++ < REG_NUMBER)
		registeries[n] = 0;
}

static void init_carriage(t_data *data, t_carriage *temp, int i)
{
	temp->id = i;
	temp->carry = false;
	//code pointer
	temp->cursor = data->champions[i]->start_addr;
	//last live  statement?
	//cycles_remaining;
	//byte_jum_size
	init_carriage_registries(temp->registeries, i);
}

static void add_carriage(t_data *data, t_carriage **head, int i)
{
	t_carriage *temp;

	temp = malloc(sizeof(t_carriage));
	if (!temp)
		exit (0); //make error function?
	
	if (*head == NULL)
		temp->next = NULL;
	else
		temp->next = *head;
	init_carriage(data, temp, i);
	*head = temp;
}

void create_carriages(t_data *data, t_carriage **head)
{
	int i;

	i = 1;
	while (i <= data->champions_num)
	{
		//malloc carriage and add to list
		add_carriage(data, head, i);
		i++;
	}
}
