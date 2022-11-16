/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:25 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/07 14:01:26 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	error(int error_number)
{
	if (error_number == OPEN_ERR)
		ft_puterror("ERROR: Failed to open received file\n");
	if (error_number == ARG_ERR)
		ft_puterror("ERROR: Invalid amount of arguments\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("ERROR: Malloc returned NULL!\n");
	if (error_number == NULL_ERR)
		ft_puterror("ERROR: NULL was passed to the function!\n");
	if (error_number == INVALID_LABEL)
		ft_puterror("ERROR: Label contained invalid characters!\n");
	if (error_number == NAME_LEN_ERR)
		ft_puterror("ERROR: Champion name too long (Max length 128)\n");
	exit(error_number);
}

static void	init_vector(t_data *s_data)
{
	s_data->vec_info = (t_vec *)malloc(sizeof(t_vec));
	if (!s_data->vec_info)
		error(MALLOC_ERR);
	vec_new_arr(s_data->vec_info, 2);
}

/*
Initializes all structs from the stack memory.
Then initializes pointers to those structs to t_data struct;
*/
static void	init_structs(t_data *s_data)
{
	t_header	s_header;
	t_error_log	s_error_log;

	s_header.magic = COREWAR_EXEC_MAGIC;
	// s_header.prog_name = NULL;
	// s_header.prog_size = ;
	// s_header.comment = ;
	s_error_log.line = 0;
	s_error_log.column = 0;
	s_data->vec_info = NULL;
	s_data->s_header = &s_header;
	s_data->s_error_log = &s_error_log;
}

int main (int argc, char *argv[])
{
	t_data			s_data;

	if (argc != 2)
		error(ARG_ERR);
	init_structs(&s_data);
	init_vector(&s_data);
	read_input(argv[1], &s_data);
	
	// Lexical analysis
		// Read byte by byte
		// Make tokens
		// 

	return (0);
}
