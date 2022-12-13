/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/12/09 15:24:38 by wdonnell         ###   ########.fr       */
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
		ft_printf("\t\t\t - 2 : Show cycles\n");
		ft_printf("\t\t\t - 4 : Show operations\n");
		ft_printf("\t\t\t - 8 : Show deaths\n");
		ft_printf("\t\t\t - 16 : Show cursor movements\n");
		
	}
	exit (1);
}

static void free_processes(t_data *data)
{
	t_process *temp;
	t_process *cur;

	temp = data->head;
	while (temp)
	{
		cur = temp;
		temp = temp->next;
		free(cur);
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
		create_processes(&data);
		print_contestants(&data);
		play_game(&data);
		print_last_alive(&data);
	}
	else
		error(NULL, "Too few arguments", 1);
	free_processes(&data);
	//free champions
	return (0);
}
