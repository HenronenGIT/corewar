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
	if (error_number == TEMP_ERR)
		ft_puterror("ERROR: TEMPORARY ERROR MESSAGE!\n");
	exit(error_number);
}



static void	init_structs(t_header *s_header, t_data *s_data)
{
	s_header->magic = COREWAR_EXEC_MAGIC;
	//! init all zeros and nulls
	s_data->header = s_header;
}

int main (int argc, char *argv[])
{
	t_header	s_header;
	t_data		s_data;

	if (argc != 2)
		error(ARG_ERR);
	init_structs(&s_header, &s_data);
	read_input(argv[1], &s_data);
	// Lexical analysis
		// Read byte by byte
		// Make tokens
		// 

	return (0);
}
