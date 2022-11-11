/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:04:25 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/10 15:58:52 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

void play_game(t_data *data, t_carriage *head)
{
	t_carriage *temp;

	while //some condition related to cycles
	{
		temp = head;
		while (temp)
		{
			//execute current carriage 
			temp = temp->next;
		}
		//do whatever checks
		data->cycles_passed++;
	}
}
