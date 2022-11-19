/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/16 10:03:41 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	error(char **str, char *msg, int usage)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	if (usage)
		ft_printf("Usage: ./corewar [-dump <num>] [-n <num>] <champion.cor> <...>\n");
	exit (1);
}

//tester
void print_arena(int8_t *arena)
{
	int i = 0;
	int j;

	printf("\nARENA--->>>\n");
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 64)
		{
			printf("%02X ", (uint8_t)arena[i]);
			i++;
			j++;
		}
		printf("\n");
	}
}

int	main(int ac, char **av)
{
	t_data	data;
	t_process *head;

	head = NULL;
	if (ac >= 2)
	{
		init_data(&data);
		parse(ac, av, &data);
		load_arena(&data);

		// print_arena(data.arena);
		parse_dump(&ac, &av, &data);
		create_processes(&data, &head);
		//play_game(&data, head);
	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	return (0);
}
