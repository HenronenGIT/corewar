/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/17 12:34:57 by wdonnell         ###   ########.fr       */
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

//tester
void print_arena(int8_t *arena)
{
	int i = 0;
	int j;

	printf("\nARENA--->>>\n");
	while (i < MEM_SIZE)
	{
		j = 0;
		while (j < 16)
		{
			//printf("%02X ", (uint8_t)arena[i]);
			
			printf("%c%c%c%c%c%c%c%c ",\
				(arena[i] & 0x80 ? '1' : '0'), \
				(arena[i] & 0x40 ? '1' : '0'), \
				(arena[i] & 0x20 ? '1' : '0'), \
				(arena[i] & 0x10 ? '1' : '0'), \
				(arena[i] & 0x08 ? '1' : '0'), \
				(arena[i] & 0x04 ? '1' : '0'), \
				(arena[i] & 0x02 ? '1' : '0'), \
				(arena[i] & 0x01 ? '1' : '0') );
			
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

		print_arena(data.arena);
		//parse_dump(&ac, &av, &data);
		create_processes(&data, &head);
		play_game(&data, head);
	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	
	//free processes
	//free champions
	return (0);
}
