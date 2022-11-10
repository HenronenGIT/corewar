/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/10 12:05:24 by akilk            ###   ########.fr       */
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
	code_size - size of champion's code
	code - champion's executable code
*/

typedef struct			s_champion
{
	int32_t				*id;
	char				*name;
	char				*comment;
	int32_t				code_size;
	char				*code;
	struct s_champion	*next;
}						t_champion;

/*
	Virtual arena:

	arena - initialized space in memory
	champions_num - number of champions
	champions - list of champions(max 4)
*/

typedef struct	s_vm
{
	char		arena[MEM_SIZE];
	int			champions_num;
	t_champion	*champions[MAX_PLAYERS];
}				t_vm;

/* corewar_main.c */
int	error(char **str, char *msg);
int	main(int argc, char **argv);

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
t_champion	*init_champion(int id);
void	init_vm(t_vm *vm);
void	load_arena(t_vm *vm);

/* parse.c */
void	parse(int argc, char **argv, t_vm *vm);

#endif
