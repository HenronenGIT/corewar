/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:22:52 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/11 15:22:52 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	save_name(char *str, t_data *s_data)
{
	// printf("%s %d\n", __FUNCTION__, __LINE__);
	PRINT(str);
}

static void	validate_name_or_comment(char *str, t_data *s_data)
{
	// printf("%s\n", str);
	
	if (!ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
		save_name(str, s_data);
	if (!ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
		//save comment
	error(TEMP_ERR);
}

static void	read_header(int fd, t_data *s_data)
{
	char	*line;
	size_t	column;
	size_t	line_count;
	size_t	i;

	line_count = 1;
	i = 0;
	while (get_next_line(fd, &line) != 0)
	{
		column = 0;
		// if (ft_is_whitespace(line[column]))
		while (ft_is_whitespace(line[column]))
			column += 1;
		if (line[column] == '.')
			validate_name_or_comment(&line[column], s_data);
		
		// printf("%s", line);
		line_count += 1;
	}
}

void	read_input(char *input, t_data *s_data)
{
	int		fd;
	char	*line;
	
	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd, s_data);
	while (get_next_line(fd, &line) != 0)
	{

		// printf("%s\n", line);
		// lexical_analysis(line);
	}
}