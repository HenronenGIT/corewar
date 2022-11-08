/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 07:08:33 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Check if champion's filename is ending with extension .cor
*/

int	is_file(char *file)
{
	if ( ft_strlen(file) >= 4)
		return (!ft_strcmp(ft_strchr(file, '\0') - ft_strlen(".cor"), ".cor"));
	else
		return (0);
}

/* Parsing champions name, codesize, comment */
void	parse_champions(char *name, t_vm *vm)
{
	printf("s:%s\n", name);
	vm->champions_num++;
}

/* Parsing arguments */

void	parse(int argc, char **argv, t_vm *vm)
{
	t_champion	*list;

	list = NULL;
	argv++;
	while (argc > 1)
	{
		/* if (!ft_strcmp(*argv, "-dump")
			parse_dump();
		*/
		/* else if (!ft_strcmp(*argv, "-n")
			parse_n_flag();
		*/
		if (is_file(*argv))
		{
			parse_champions(*argv, vm);
		}
		// printf("s:%s\n", *argv);
		argv++;
		argc--;
	}
	printf("num:%d\n", vm->champions_num);
}
