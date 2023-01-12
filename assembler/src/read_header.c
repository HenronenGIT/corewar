/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_header.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 08:50:47 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/15 08:50:48 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Iterates trough string, trying to find starting quote of the name or comment
*/
static void	seek_quote(t_data *s_data, char *string, int fd, t_type type)
{
	size_t	i;
	char	*buffer;

	i = 0;
	buffer = NULL;
	if (type == NAME)
		i = NAME_CMD_LEN;
	else if (type == COMMENT)
		i = COMMENT_CMD_LEN;
	while (string[i] != '\0')
	{
		s_data->s_error_log->column = i + 2;
		if (string[i] == STRING_CHAR)
		{
			buffer = save_to_buffer(s_data, &string[i], fd);
			save_header(s_data, buffer, type);
			ft_strdel(&buffer);
			return ;
		}
		if (is_delim(string[i]) == false)
			lexical_error(s_data);
		i += 1;
	}
	lexical_error(s_data);
}

/*
Iterates trough "line" and seeks HEADER_CHAR ".".
When HEADER_CHAR is found, function checks that was the word .name or .comment
*/
static void	seek_header_char(t_data *s_data, char *line, int fd)
{
	size_t	i;

	i = 0;
	while (line[i] != '\0')
	{
		if (ft_is_whitespace(line[i]))
			i += 1;
		else if (line[i] == COMMENT_CHAR)
			return ;
		else if (line[i] == HEADER_CHAR)
		{
			if (ft_strncmp(&line[i], NAME_STRING, NAME_CMD_LEN) == 0)
				seek_quote(s_data, &line[i], fd, NAME);
			else if (ft_strncmp(&line[i], COMMENT_STRING, COMMENT_CMD_LEN) == 0)
				seek_quote(s_data, &line[i], fd, COMMENT);
			else
				lexical_error(s_data);
			return ;
		}
		else
			lexical_error(s_data);
		s_data->s_error_log->column += 1;
	}
}

/*
Read header information .name and .comment.
*/
void	read_header(int fd, t_data *s_data)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		s_data->s_error_log->column = 1;
		seek_header_char(s_data, line, fd);
		if (s_data->s_header->name_saved && s_data->s_header->comment_saved)
			break ;
		free(line);
		s_data->s_error_log->line += 1;
	}
	free(line);
	if (!s_data->s_header->name_saved || !s_data->s_header->comment_saved)
		lexical_error(s_data);
}
