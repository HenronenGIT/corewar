/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:24:29 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 07:16:21 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

int	main(int argc, char **argv)
{
	t_vm	vm;

	if (argc >= 2)
	{
		init_vm(&vm);
		printf("num1:%d\n", vm.champions_num);
		parse(argc, argv, &vm);
	}
	/*
	else
		print usage
	*/
	return (0);
}
