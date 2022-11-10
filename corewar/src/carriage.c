/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   carriage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:55:35 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 11:39:14 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

init_carriage_registries(int8_t *registeries, int i)
{
	int n;

	registeries[0] = -i;
	n = 1;
	while (n++ < REG_NUMBER)
		registeries[n] = 0;
}

static init_carriage_info(t_carriage *temp, int i)
{
	temp->id = i;
	temp->carry = false;
	//code pointer
	//last live  statement?
	//cycles_remaining;
	//current position pointer
	//byte_jum_size
	init_carriage_registries(temp->registeries, i);

}

static add_carriage(t_carriage *head, int i)
{
	t_carriage *temp;

	temp = malloc(sizeof(t_carriage));
	if (!temp)
		exit (0); //make error function?
	
	if (!head)
		temp->next = NULL;
	else
		temp->next = head;
	init_carriage_info(temp, i);
	return (head = temp);
}

t_carriage *init_carriage(t_vm *vm, t_carriage *head)
{
	int i;

	i = 1;
	while (i <= vm->champions_num)
	{
		//malloc carriage and add to list
		head = add_carriage(head, i);
		i++;
	}
	return head;

}
