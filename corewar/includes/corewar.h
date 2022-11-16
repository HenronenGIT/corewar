/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/11/16 14:02:45 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "../../includes/op.h"
#include "../../libft/includes/libft.h"
#include "../../libft/includes/ft_printf.h"
#include <fcntl.h>
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
	int					id;
	char				*name;
	char				*comment;
	int32_t				code_size;
	char				*code;
	int					start_addr;
	struct s_champion	*next;
}						t_champion;

/*
	Virtual arena:

	arena - initialized space in memory
	champions_num - number of champions
	champions - list of champions(max 4)
	dump_cycles - after this number of executions,
	dump the memory on the standard output and quit the game.

*/

//game paramaters

typedef struct s_data
{
	int8_t		arena[MEM_SIZE];
	int			champions_num;
	t_champion	*champions[MAX_PLAYERS];
	int			dump_cycle;
	int			last_alive_player;
	int			cycles_passed;
	int			num_live_statements;
	int			cycles_to_die;
	int			num_checks_performed;
}	t_data;



typedef struct s_process
{
	int id;
	bool carry;
	//The statement code on which the process stands:
	//Prior to the battle, the value of this variable is not set.
	int cursor;
	int last_live;
	int cycles_remaining;
	int byte_jump_size;
	int32_t registeries[REG_NUMBER];
	struct s_process *next;
}				t_process;

/* corewar_main.c */
int	error(char **str, char *msg, int usage);
int	main(int argc, char **argv);

/* init.c */
t_champion	*init_champion(void);
void	init_data(t_data *data);
void	load_arena(t_data *data);
void	create_processes(t_data *data, t_process **head);

/* parse.c */
void	parse(int ac, char **av, t_data *data);
void	parse_champions(char *file, t_champion *champion);

/* parse_flags.c */
void	parse_dump(int *ac, char ***av, t_data *data);
void	reset_ids(t_data *data);
void	parse_n(int *ac, char ***av, t_data *data, t_champion *champion);

/* utils.c */
bool	is_cor_file(char *file);
int32_t	bytes2int(uint8_t *byte_value, size_t size);

/* play */
void	play_game(t_data *data, t_process *head);

#endif
