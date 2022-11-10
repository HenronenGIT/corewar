/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/10 15:31:01 by wdonnell         ###   ########.fr       */
=======
/*   Updated: 2022/11/10 11:39:59 by wdonnell         ###   ########.fr       */
>>>>>>> f7c9ee7b3ae55b9f4c48eb960dddd84f36fe3b64
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
	t_carriage *head;

	head = NULL;
	if (ac >= 2)
	{
		parse(ac, av, &data);
		load_arena(&data);
		init_data(&data);
		create_carriages(&data, &head);
		play_game(&data, head);
	}
	else
	//make exit type function
		printf("TEST USAGE\n");
	return (0);
}
