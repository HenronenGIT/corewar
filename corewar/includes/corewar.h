/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/10 15:06:00 by wdonnell         ###   ########.fr       */
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
	int				id;
	char				*name;
	char				*comment;
	int32_t				code_size;
	char				*code;
	//char				*start_addr;
	struct s_champion	*next;
}						t_champion;

/*
	Virtual arena:

	arena - initialized space in memory
	champions_num - number of champions
	champions - list of champions(max 4)
*/

//game paramaters

typedef struct s_data
{
	int8_t		arena[MEM_SIZE];
	int			champions_num;
	t_champion	*champions[MAX_PLAYERS];
	struct s_champion *last_alive;
	int			cycles_passed;
	int			num_live_statements;
	int			cycles_to_die;
	int			num_checks_performed;
}	t_data;



typedef struct s_carriage
{
	int id;
	bool carry;
	//The statement code on which the carriage stands:
	//Prior to the battle, the value of this variable is not set.
	int cursor;
	int last_live;
	int cycles_remaining;
	int current_position; //memory address
	int byte_jump_size;
	int32_t registeries[REG_NUMBER];
	struct s_carriage *next;
}				t_carriage;

/* corewar_main.c */
int	error(char **str, char *msg);
int	main(int argc, char **argv);

/* init.c */
t_champion	*init_champion(int id);
void	init_data(t_data *data);
void	load_arena(t_data *data);
void	create_carriages(t_data *data, t_carriage **head);

/* parse.c */
void	parse(int argc, char **argv, t_data *data);

#endif
