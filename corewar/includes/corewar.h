/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 13:43:41 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include <stdlib.h>
#include "../../includes/op.h"
#include "../../libft/libft.h"
#include <stdio.h> // remove

/*
	Champion:
	id - id number of champion
	name - champion's name
	comment - champion's comment
	code_size - size of champion's code
	code - champion's executable code
*/

typedef struct s_champion
{
	int32_t	*id;
	char	*name;
	char	*comment;
	int32_t	code_size;
	uint8_t	*code;

}	t_champion;

/*
	Virtual arena:

	arena - initialized space in memory
	champions - list of champions
*/

typedef struct	s_vm
{
	char		arena[MEM_SIZE];
	t_champion	champions[MAX_PLAYERS];
	int			champions_num;
}	t_vm;

/* corewar_main.c */
int	error(char **str, char *msg);
int	main(int argc, char **argv);

/* init.c */
t_champion	*init_champion(int id);
t_vm	*init_vm(void);

/* parse.c */
void	parse(int argc, char **argv, t_vm *vm);

#endif
