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
#include <stdio.h>

void	error(int error_number)
{
	if (error_number == OPEN_ERR)
		ft_puterror("ERROR: Failed to open received file\n");
	if (error_number == ARG_ERR)
		ft_puterror("ERROR: Invalid amount of arguments\n");
	exit(error_number);
}

static void	read_input(char *input)
{
	int		fd;
	char	*line;
	
	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	while (get_next_line(fd, &line) != 0)
	{
		// printf("%s\n", line);

		//! Make line counter and column counter for error messages.
	}
}

static void	init_struct(t_header *s_header)
{
	s_header->magic = COREWAR_EXEC_MAGIC;
}

int main (int argc, char *argv[])
{
	t_header	s_header;

	if (argc != 2)
		error(ARG_ERR);
	init_struct(&s_header);
	read_input(argv[1]);
	// Lexical analysis
		// Read byte by byte
		// Make tokens
		// 

	return (0);
}