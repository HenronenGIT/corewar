/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/12/15 14:42:18 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int	error(char **str, char *msg, int usage)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	if (usage)
	{
		ft_printf("\nUsage: ");
		ft_printf("./corewar [-dump <num>] [-n <num>] [-v <num>]");
		ft_printf(" <champion.cor> <...>\n");
		ft_printf("\n#### OUTPUT MODES ####\n");
		ft_printf("\t-dump <num> : Dumps memory after <num> cycles and exits\n");
		ft_printf("\t-v <num> : ");
		ft_printf("Verbosity levels, add together to enable several\n");
		ft_printf("\t\t - 1 : ");
		ft_printf("Mimic supplied VM\n");
		ft_printf("\t\t\t(hide live statements, hide aff, immplement 'lld' bug)\n");
		ft_printf("\t\t - 2 : Show cycles\n");
		ft_printf("\t\t - 4 : Show operations\n");
		ft_printf("\t\t - 8 : Show deaths\n");
		ft_printf("\t\t - 16 : Show cursor movements\n");
	}
	exit (1);
}

static void	free_champions(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->champions_num)
	{
		free (data->champions[i]->name);
		free (data->champions[i]->comment);
		free (data->champions[i]->code);
		free (data->champions[i]);
		i++;
	}
}

void	load_arena(t_data *data)
{
	int	current;
	int	start;

	current = 0;
	start = 0;
	while (current < data->champions_num)
	{
		start = (current * MEM_SIZE) / data->champions_num;
		data->champions[current]->start_addr = start;
		ft_memcpy(&(data->arena[start]), data->champions[current]->code,
			data->champions[current]->code_size);
		current++;
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
	free_champions(&data);
	return (0);
}
