/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 15:54:53 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H

# define COREWAR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../includes/op.h"
#include "../../libft/libft.h"
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
	int			champions_num;
}	t_vm;


typedef struct s_data
{
	int last_alive_player;
	int cycles_passed;
	int num_live_statements;
	int cycles_to_die;
	int num_checks_performed;

}				t_data;

typedef struct s_carriage
{
	int id;
	bool carry;
	//The statement code on which the carriage stands:
	//Prior to the battle, the value of this variable is not set.
	int last_live;
	int cycles_remaining;
	int current_position; //memory address
	int byte_jump_size;
	int8_t registeries[REG_NUMBER];
}				t_carriage;

/* corewar_main.c */
int	error(char **str, char *msg);
int	main(int argc, char **argv);

/* init.c */
void	init_champion(t_champion *champion);
t_vm	*init_vm(void);

/* parse.c */
void	parse(int argc, char **argv, t_vm *vm);

#endif
