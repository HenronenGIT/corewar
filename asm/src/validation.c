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

void save_token(char *sub_string, t_type type)
{

}

void lexical_scanner(char *line, t_data *data)
{
	unsigned int left;
	unsigned int right;
	int len;
	char *sub_string;

	left = 0;
	right = 0;
	len = ft_strlen(line);
	sub_string = NULL;
	while (right <= len && left <= right)
	{
		if (is_delimiter(line[right]) == false)
			right += 1;
		if (is_delimiter(line[right] == true && left != right))
		{
			sub_string = ft_strsub(line, left, right - left);
			if (!sub_string)
				error(MALLOC_ERR);
			// if (ft_strcmp(sub_string, NAME_CMD_STRING) == 0)
			// 	save_token(sub_string, NAME);
			// else if (ft_strcmp(sub_string, COMMENT_CMD_STRING) == 0)
			// 	save_token(sub_string, COMMENT);
			if (is_statement(sub_string))
				save_token(sub_string, STATEMENT);
			else if (is_label(sub_string, data))
				save_token(sub_string, LABEL);
		}
	}
}

/*
Read header information: .name and .comment
*/
void	read_header(int fd, t_data *s_data)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{

	}

}

/*
Opens file descriptor for input reading.
After that while loops starts reading file descriptor line by line.
Every single line is sent to lexical_scanner function to be tokenized.
*/
void read_input(char *input, t_data *s_data)
{
	int fd;
	char *line;

	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd, s_data);
	while (get_next_line(fd, &line) != 0)
		lexical_scanner(line, s_data);
}
