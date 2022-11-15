/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/15 11:10:04 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	error(char **str, char *msg, int usage)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	if (usage)
		printf("Usage: ./corewar [-dump <num>] [-n <num>] <champion.cor> <...>\n");
	exit (1);
}

int	main(int ac, char **av)
{
	t_data	data;
	// t_carriage *head;

	// head = NULL;
	if (ac >= 2)
	{
		init_data(&data);
		parse(ac, av, &data);
		load_arena(&data);
		// create_carriages(&data, &head);
		// play_game(&data, head);
	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	return (0);
}
