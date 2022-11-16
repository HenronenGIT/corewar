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

// static char	*skip_white_spaces(char *str)
// {
	
// }

static void	find_quotes(char *line, size_t *first_quote, size_t *second_quote)
{
	size_t	i;

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

void validate_comment(t_data *s_data, char *line)
{
	size_t	i;

	i = COMMENT_CMD_LEN;
	// find_quotes(&line[i], &first_quote, &second_quote);

}

static void validate_name(t_data *s_data, char *line)
{
	// check datatypes. is unsigned int good?
	size_t i;
	size_t first_quote;
	size_t second_quote;
	size_t name_len;

	name_len = 0;
	first_quote = 0;
	second_quote = 0;
	i = NAME_CMD_LEN;
	find_quotes(&line[i], &first_quote, &second_quote);
	if (second_quote == 0)
		lexical_error(s_data, line, TEMP_ERR);
	name_len = (second_quote - first_quote) - 1;
	if (name_len > PROG_NAME_LENGTH)
		error(NAME_LEN_ERR);
	first_quote += NAME_CMD_LEN;
	second_quote += NAME_CMD_LEN + 1;
	while (line[second_quote] != '\0')
	{
		if (is_delimiter(line[second_quote]) == false)
			lexical_error(s_data, line, TEMP_ERR);
		second_quote += 1;
	}
	ft_strncpy(s_data->s_header->prog_name, &line[first_quote + 1], name_len);
	// PRINT(s_data->s_header->prog_name);
	printf("%s\n", s_data->s_header->prog_name);
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
				validate_name(s_data, &line[i]);
			else if (ft_strncmp(&line[i], COMMENT_CMD_STRING, COMMENT_CMD_LEN) == 0)
				validate_comment(s_data, &line[i]);
			else
				lexical_error(s_data, line, TEMP_ERR);
			break;
		}
		i += 1;
	}
	LOCATION;
}

/*
Read header information: .name and .comment
*/
void read_header(int fd, t_data *s_data)
{
	char *line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		s_data->s_error_log->line += 1;
		seek_header_keywords(s_data, line);
		free(line);
	}
}
