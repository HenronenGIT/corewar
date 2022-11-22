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

static void find_quotes(char *line, size_t *first_quote, size_t *second_quote)
{
	size_t i;

	i = 0;
	while (line[i] != '\0' && *second_quote == 0)
	{
		if (*first_quote != 0 && line[i] == STRING_CHAR)
			*second_quote = i;
		if (line[i] == STRING_CHAR && *first_quote == 0)
			*first_quote = i;
		i += 1;
	}
}

void validate_string(t_data *s_data, char *line, int type)
{
	size_t i;
	size_t first_quote;
	size_t second_quote;
	size_t str_len;

	i = 0;
	str_len = 0;
	first_quote = 0;
	second_quote = 0;
	find_quotes(&line[i], &first_quote, &second_quote);
	if (second_quote == 0)
		lexical_error(s_data, line, TEMP_ERR);
	str_len = (second_quote - first_quote) - 1;
	if (type == NAME && str_len > PROG_NAME_LENGTH)
		error(NAME_LEN_ERR);
	else if (type == COMMENT && str_len > COMMENT_LENGTH)
		error(COMMENT_LEN_ERR);
	while (line[++second_quote] != '\0')
	{
		if (is_delimiter(line[second_quote]) == false)
			lexical_error(s_data, line, TEMP_ERR);
	}
	if (type == NAME)
		ft_strncpy(s_data->s_header->prog_name, &line[first_quote + 1], str_len);
	else
		ft_strncpy(s_data->s_header->comment, &line[first_quote + 1], str_len);
}

static void seek_header_keywords(t_data *s_data, char *line)
{
	size_t i;

	i = 0;
	while (line[i] != '\0')
	{
		if (is_delimiter(line[i]) == false && line[i] != HEADER_CHAR)
			lexical_error(s_data, line, TEMP_ERR);
		else if (is_delimiter(line[i]) == false)
		{
			if (ft_strncmp(&line[i], NAME_CMD_STRING, NAME_CMD_LEN) == 0)
				validate_string(s_data, &line[i + NAME_CMD_LEN], NAME);
			else if (ft_strncmp(&line[i], COMMENT_CMD_STRING, COMMENT_CMD_LEN) == 0)
				validate_string(s_data, &line[i + COMMENT_CMD_LEN], COMMENT);
			else
				lexical_error(s_data, line, TEMP_ERR);
			break;
		}
		i += 1;
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
		seek_header_keywords(s_data, line);
		if (*(prog_name) != '\0' && *(comment) != '\0')
			break;
		free(line);
	}
}
