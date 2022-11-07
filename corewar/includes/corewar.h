/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/07 13:39:34 by akilk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include "../../includes/op.h"
#include <stdio.h> // remove

/*
	Champion:
	id - id number of champion
	name - champion's name
	comment - champion's comment
*/

typedef struct s_champion
{
	int32_t	*id;
	char	*name;
	char	*comment;
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
}	t_vm;


/* init.c */
void	init_vm(t_vm *vm);

#endif