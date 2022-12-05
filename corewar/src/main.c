/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/12/05 15:33:52 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	error(char **str, char *msg, int usage)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	if (usage)
	{
		ft_printf("###########################################################################\n");
		ft_printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>CORE WAR<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");
		ft_printf("###########################################################################\n");
		ft_printf("░░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░\n");
		ft_printf("░░░░░▄▄████▄▄░░░░░  ░░░░░▀▄░░░▄▀░░░░░  ░░░▄░▀▄░░░▄▀░▄░░░  ░░░░▄▄████▄▄░░░░░\n");
		ft_printf("░░░▄██████████▄░░░  ░░░░▄█▀███▀█▄░░░░  ░░░█▄███████▄█░░░  ░░░██████████░░░░\n");
		ft_printf("░▄██▄██▄██▄██▄██▄░  ░░░█▀███████▀█░░░  ░░░███▄███▄███░░░  ░░░██▄▄██▄▄██░░░░\n");
		ft_printf("░░░▀█▀░░▀▀░░▀█▀░░░  ░░░█░█▀▀▀▀▀█░█░░░  ░░░▀█████████▀░░░  ░░░░▄▀▄▀▀▄▀▄░░░░░\n");
		ft_printf("░░░░░░░░░░░░░░░░░░  ░░░░░░▀▀░▀▀░░░░░░  ░░░░▄▀░░░░░▀▄░░░░  ░░░▀░░░░░░░░▀░░░░\n");
		ft_printf("░░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░  ░░░░░░░░░░░░░░░░░\n");
		ft_printf("Usage: ./corewar [-dump <num>] [-n <num>] [-v <num>] <champion.cor> <...>\n");
		ft_printf("#### OUTPUT MODE ##########################################################\n");
		ft_printf("\t-dump <num>\t: Dumps memory after <num> cycles and exits\n");
		ft_printf("\t-v <num>\t: Verbosity levels, can be added together to enable several\n");
		ft_printf("\t\t\t - 1 : Show operations\n");
		ft_printf("\t\t\t - 2 : Show cursor movements\n");
		ft_printf("\t\t\t - 4 : Show cycles\n");
	}
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
		while (j < 32)
		{
			printf("%02X ", (uint8_t)arena[i]);

			/*
			printf("%c%c%c%c%c%c%c%c ",\
				(arena[i] & 0x80 ? '1' : '0'), \
				(arena[i] & 0x40 ? '1' : '0'), \
				(arena[i] & 0x20 ? '1' : '0'), \
				(arena[i] & 0x10 ? '1' : '0'), \
				(arena[i] & 0x08 ? '1' : '0'), \
				(arena[i] & 0x04 ? '1' : '0'), \
				(arena[i] & 0x02 ? '1' : '0'), \
				(arena[i] & 0x01 ? '1' : '0') );
			*/
			i++;
			j++;
		}
		printf("\n");
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac >= 2)
	{
		init_data(&data);
		parse(ac, av, &data);
		load_arena(&data);
		// to add: print_introduction(players, id)
		create_processes(&data);
		play_game(&data);
	}
	else
		error(NULL, "Too few arguments", 1);

	//free processes
	//free champions
	return (0);
}
