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

// void	lexical_analysis(char *line)
// {
// 	static size_t	line_count;
// 	size_t			i;

// 	i = 0;
// 	while (line[i] != '\0')
// 	{
// 		if (line[i] == '.')

// 		i += 1;
// 	}
// }

static void	read_header(int fd)
{
	char	*line;
	size_t	i;

	i = 0;
	while (get_next_line(fd, &line) != 0)
	{
		if (line[i] != NAME_CMD_STRING[i])
		i += 1;
	}
}

static void	read_input(char *input)
{
	int		fd;
	char	*line;
	
	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd);
	// loop for reading rest of the file
	while (get_next_line(fd, &line) != 0)
	{
		printf("%s\n", line);
		// lexical_analysis(line);
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