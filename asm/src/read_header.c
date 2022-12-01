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

static void reel_to_end(char *string)
{
	while (*string != '\0')
	{
		if (!is_delimiter(*string))
			error(TEMP_ERR);
		string += 1;
	}
}

//? Check if can make better or shorter
static char *copy_name(t_data *s_data, char *string, int fd, t_type type)
{
	size_t j;
	char *dst;

	j = 0;
	if (type == NAME)
	{
		if (s_data->s_header->name_saved == true)
			error(NAME_COUNT_ERR);
		dst = s_data->s_header->prog_name;
		s_data->s_header->name_saved = true;
	}
	else if (type == COMMENT)
	{
		if (s_data->s_header->comment_saved == true)
			error(COMMENT_COUNT_ERR);
		dst = s_data->s_header->comment;
		s_data->s_header->comment_saved = true;
	}
	while (*string != STRING_CHAR)
	{
		if (*string == '\0')
		{
			dst[j] = '\n';
			get_next_line(fd, &string);
		}
		else
		{
			dst[j] = *string;
			string += 1;
		}
		j += 1;
	}
	if (type == NAME && ft_strlen(dst) > PROG_NAME_LENGTH)
		error(NAME_LEN_ERR);
	else if (type == COMMENT && ft_strlen(dst) > COMMENT_LENGTH)
		error(COMMENT_LEN_ERR);
	return (string);
}

static void seek_quote(t_data *s_data, char *string, int fd, t_type type)
{
	size_t i;

	i = 0;
	if (type == NAME)
		i = NAME_CMD_LEN;
	else if (type == COMMENT)
		i = COMMENT_CMD_LEN;
	while (string[i] != '\0')
	{
		if (string[i] == STRING_CHAR)
		{
			string = copy_name(s_data, &string[i + 1], fd, type);
			reel_to_end(++string);
			return;
		}
		if (is_delimiter(string[i]) == false)
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
	size_t left;
	size_t right;

	left = 0;
	right = 0;
	while (line[right] != '\0')
	{
		if (line[right] == HEADER_CHAR && left != right)
			left = right;
		else if (is_delimiter(line[right]) && line[left] == HEADER_CHAR)
		{
			if (ft_strncmp(&line[left], NAME_CMD_STRING, NAME_CMD_LEN) == 0)
				seek_quote(s_data, &line[left], fd, NAME);
			else if (ft_strncmp(&line[left], COMMENT_CMD_STRING, COMMENT_CMD_LEN) == 0)
				seek_quote(s_data, &line[left], fd, COMMENT);
			else
				lexical_error(s_data);
			return;
		}
		else
			right += 1;
	}
}

/*
Read header information: .name and .comment
*/
void	read_header(int fd, t_data *s_data)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		s_data->s_error_log->line += 1;
		seek_header_char(s_data, line, fd);
		if (s_data->s_header->name_saved && s_data->s_header->comment_saved)
			return;
		free(line);
	}
	if (!s_data->s_header->name_saved || !s_data->s_header->comment_saved)
		lexical_error(s_data);
}
