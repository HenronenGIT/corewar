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

static void copy_name(t_data *s_data, char *string, int fd, t_type type)
{
	size_t i;
	size_t j;
	char *dst;

	i = 0;
	j = 0;
	if (type == NAME)
		dst = s_data->s_header->prog_name;
	else if (type == COMMENT)
		dst = s_data->s_header->comment;
	while (string[i] != STRING_CHAR)
	{
		if (string[i] == '\0')
		{
			dst[j] = '\n';
			get_next_line(fd, &string);
			i = 0;
		}
		else
		{
			dst[j] = string[i];
			i += 1;
		}
		j += 1;
	}
}
// static void copy_name(t_data *s_data, char *string, int fd, t_type type)
// {
// 	size_t i;
// 	size_t j;
// 	char *dst;

// 	i = 0;
// 	j = 0;
// 	if (type == NAME)
// 		dst = s_data->s_header->prog_name;
// 	else if (type == COMMENT)
// 		dst = s_data->s_header->comment;
// 	while (string[i] != STRING_CHAR)
// 	{
// 		if (string[i] == '\0')
// 		{
// 			dst[j] = '\n';
// 			get_next_line(fd, &string);
// 			i = 0;
// 		}
// 		else
// 		{
// 			dst[j] = string[i];
// 			i += 1;
// 		}
// 		j += 1;
// 	}
// }

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
			copy_name(s_data, &string[i + 1], fd, type);
			return;
		}
		if (is_delimiter(string[i]) == false)
			lexical_error(s_data);
		i += 1;
	}
	lexical_error(s_data);
}

static void seek_header_keywords(t_data *s_data, char *line, int fd)
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
			return;
		}
		else
			right += 1;
	}
}

/*
Read header information: .name and .comment
*/
void read_header(int fd, t_data *s_data)
{
	char *line;
	char *prog_name = s_data->s_header->prog_name;
	char *comment = s_data->s_header->comment;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		s_data->s_error_log->line += 1;
		seek_header_keywords(s_data, line, fd);
		if (*(prog_name) != '\0' && *(comment) != '\0')
			return ;
		free(line);
	}
	if (*(prog_name) == '\0' || *(comment) == '\0')
		lexical_error(s_data);
}
