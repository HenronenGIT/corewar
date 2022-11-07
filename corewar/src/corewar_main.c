/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/07 15:31:18 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	main(int argc, char **argv)
{
	t_vm	vm;

	if (argc >= 2)
	{
		init_vm(&vm);
		parse(argc, argv, &vm);
	}
	/*
	else
		print usage
	*/
	return (0);
}