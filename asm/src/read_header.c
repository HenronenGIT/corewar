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

void validate_name(t_data *s_data, char *line)
{
	size_t	i;
	char	*first_quote;
	char	*last_quote;

	i = 0;
	first_quote = NULL;
	last_quote = NULL;
	first_quote = ft_strchr(line, STRING_CHAR);
	last_quote = ft_strrchr(line, STRING_CHAR);
	if (first_quote == NULL)
		lexical_error(s_data, line, NAME_ERR);
	while (&first_quote[++i] != last_quote)
	{
		if (first_quote[i] == STRING_CHAR)
			lexical_error(s_data, line, TEMP_ERR);
		i += 1;
	}
	// s_data->s_header->prog_name = ft_strsub(first_quote, 0, i - (int)first_quote);
	PRINT(first_quote);
	exit(0);
}

void validate_comment()
{
}

/*
Read header information: .name and .comment
*/
void read_header(int fd, t_data *s_data)
{
	char *line;
	size_t i;
	size_t name_len;
	size_t comment_len;

	i = 0;
	name_len = ft_strlen(NAME_CMD_STRING);
	comment_len = ft_strlen(COMMENT_CMD_STRING);
	line = NULL;
	while (get_next_line(fd, &line))
	{
		s_data->s_error_log->line += 1;
		while (is_delimiter(line[i]) == true || line[i] != '\0')
			i += 1;
		if (line[i] != HEADER_CHAR)
			le //!
		/* 2 style */
		// if (ft_strstr(line, NAME_CMD_STRING))
			// validate_name(s_data, line);
		// else if (ft_strstr(line, COMMENT_CMD_STRING))
			// validate_comment(s_data, &line[i + name_len]);
		// while (line[i] != '\0')
		// {
			// if (is_delimiter(line[i]) == false)
				// lexical_error(s_data, line, TEMP_ERR);
		// }

		/* 1 style */
		// if (ft_str)
		// while (is_delimiter(line[i]) == true || line[i] != '\0')
			// i += 1;
		// if (line[i] != '\0' && line[i] != HEADER_CHAR) //! double check that works.
			// lexical_error(s_data, line, TEMP_ERR);
		// if (ft_strncmp(&line[i], NAME_CMD_STRING, name_len) == 0)
			// validate_name(s_data, &line[i + name_len]); //AAAAAA
		// else if (ft_strncmp(&line[i + comment_len], COMMENT_CMD_STRING, comment_len) == 0)
			// validate_comment(&line[i]);
		free(line);
		i = 0;
	}
}
