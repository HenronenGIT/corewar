/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   corewar.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:41:19 by akilk             #+#    #+#             */
/*   Updated: 2022/12/15 11:27:58 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COREWAR_H
# define COREWAR_H

# include <stdlib.h>
# include <stdbool.h>
# include <stdint.h>

# include "../../includes/op.h"
# include "../../libft/includes/libft.h"
# include "../../libft/includes/ft_printf.h"
# include <fcntl.h>

typedef struct s_champion
{
	int					id;
	char				*name;
	char				*comment;
	int32_t				code_size;
	char				*code;
	int					start_addr;
}						t_champion;

typedef struct s_data
{
	int8_t				arena[MEM_SIZE];
	int					champions_num;
	t_champion			*champions[MAX_PLAYERS];
	size_t				num_processes;
	int					dump_cycle;
	int					cycles_total;
	int					cycles_to_die;
	int					cycles_after_check;
	int					num_checks_performed;
	int					last_alive_champ;
	int					num_live_statements;
	int					new_cursor;
	int					verbosity;
	int					new_process_id;
	struct s_process	*head;
	struct s_process	*parent;

}	t_data;

typedef struct s_process
{
	int					id;
	bool				carry;
	int8_t				statement_code;
	int					cursor;
	int					last_live;
	int					cycles_remaining;
	int					byte_jump_size;
	int32_t				registers[REG_NUMBER];
	struct s_process	*next;
}				t_process;

/* corewar_main */
int			error(char **str, char *msg, int usage);
int			main(int argc, char **argv);

/* init */
t_champion	*init_champion(void);
void		init_data(t_data *data);
void		init_process(t_data *data, t_process *temp, int i);
void		init_fork(t_data *data, t_process *temp, int i);
void		load_arena(t_data *data);

/* processes */
void		create_processes(t_data *data);
void		add_process(t_data *data, t_process **head, int i);

/* parse */
void		parse(int ac, char **av, t_data *data);
//void		parse_champions(char *file, t_champion *champion);
void		parse_dump(int *ac, char ***av, t_data *data);
void		parse_n(int *ac, char ***av, t_data *data, t_champion *champion);
void		parse_verbosity(int *ac, char ***av, t_data *data);

/* ids */

void		reset_ids(t_data *data);
bool		id_used(int id, t_data *data);

/* utils */
bool		is_cor_file(char *file);
bool		valid_int(char *str);
int32_t		bytes2int(uint8_t *byte_value, int start, size_t size);

/* print */
void		print_data(t_data *data);
void		print_orig_data(t_data *data);
void		print_contestants(t_data *data);
void		print_last_alive(t_data *data);

/* play */
void		play_game(t_data *data);

/* check */
void		check(t_data *data, t_process **head);

#endif
