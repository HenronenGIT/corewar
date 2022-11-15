/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/15 11:01:02 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void play_game(t_data *data, t_process *head)
{
	t_process *temp;

	while //some condition related to cycles
	{
		temp = head;
		while (temp)
		{
			//execute current process 
			temp = temp->next;
		}
		//do whatever checks
		data->cycles_passed++;
	}
}
