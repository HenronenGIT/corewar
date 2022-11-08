/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 14:59:45 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

#include<stdio.h>

int	error(char **str, char *msg)
{
	if (str)
		ft_strdel(str);
	ft_putendl_fd(msg, 2);
	exit (1);
}

int	main(int ac, char **av)
{
	t_vm	vm;

	if (ac >= 2 && ac <= MAX_PLAYERS)
	{
		//get number of players
		//get other info, name comments etc
		//copy exec code to designated location in memory
		parse(ac, av, &vm);
		//-->init carriages
		//-->announce players
		//--->play_game



	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	return (0);
}
