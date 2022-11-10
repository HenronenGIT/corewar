/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/10 14:03:14 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	error(char **str, char *msg)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	exit (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac >= 2 && ac <= MAX_PLAYERS)
	{
		data.champions_num = 0; // add to init_data
		parse(ac, av, &data);
		load_arena(&data);
	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	return (0);
}
