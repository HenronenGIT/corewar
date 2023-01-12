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

static char	*decide_destination(t_data *s_data, t_type type)
{
	if (type == NAME)
	{
		if (s_data->s_header->name_saved == true)
			error(NAME_COUNT_ERR);
		s_data->s_header->name_saved = true;
		return (s_data->s_header->prog_name);
	}
	else
	{
		if (s_data->s_header->comment_saved == true)
			error(COMMENT_COUNT_ERR);
		s_data->s_header->comment_saved = true;
		return (s_data->s_header->comment);
	}
}


char *find_second_quote(char *string, int fd)
{
	char *result;
	char *line;
	char *last_quote;
	size_t	i;

	i = 0;
	result = NULL;
	line = NULL;
	last_quote = ft_strchr(&string[i + 1], STRING_CHAR);
	if (last_quote)
		return (&string[1]);
	// while (string[i] != STRING_CHAR)
	while (get_next_line(fd, &line))
	{
		if (ft_strchr(line, STRING_CHAR))
			break;
		else
			ft_realloc(&result, line);
			// result = ft_strjoin(result, line);
			// ft_realloc(&result, line);

	}
	return(result);
}

// static char	*copy_name(t_data *s_data, char *string, int fd, t_type type)
/*
Function that iterates trough strubg untils finds ending quote.
During iteration saves all bytes to s_header struct.
*/
static void	save_header(t_data *s_data, char *buffer, int fd, t_type type)
{
	size_t	j;
	char	*dst;

	j = 0;
	dst = decide_destination(s_data, type);
	while (*buffer != STRING_CHAR)
		dst[j++] = *buffer++;


	// reel_to_end(s_data, ++buffer);
	//? can be moved to own func
	if (type == NAME && ft_strlen(dst) > PROG_NAME_LENGTH)
		error(NAME_LEN_ERR);
	else if (type == COMMENT && ft_strlen(dst) > COMMENT_LENGTH)
		error(COMMENT_LEN_ERR);
	// return (string);
}
// static void	save_header(t_data *s_data, char *string, int fd, t_type type)
// {
// 	size_t	j;
// 	char	*dst;

// 	j = 0;
// 	dst = decide_destination(s_data, type);
// 	while (*string != STRING_CHAR)
// 	{
// 		if (*string == '\0')
// 		{
// 			dst[j] = '\n';
// 			get_next_line(fd, &string);
// 			ft_replace(&string, '\n', '\0');
// 		}
// 		else
// 			dst[j] = *string++;
// 		s_data->s_error_log->column += 1;
// 		j += 1;
// 	}
// 	reel_to_end(s_data, ++string);




// 	//? can be moved to own func
// 	if (type == NAME && ft_strlen(dst) > PROG_NAME_LENGTH)
// 		error(NAME_LEN_ERR);
// 	else if (type == COMMENT && ft_strlen(dst) > COMMENT_LENGTH)
// 		error(COMMENT_LEN_ERR);
// 	// return (string);
// }

/*
Iterates trough string, trying to find starting quote of the name or comment
*/
static void	seek_quote(t_data *s_data, char *string, int fd, t_type type)
{
	size_t	i;
	char	*buffer;

	buffer = NULL;
	i = 0;
	if (type == NAME)
		i = NAME_CMD_LEN;
	else if (type == COMMENT)
		i = COMMENT_CMD_LEN;
	while (string[i] != '\0')
	{
		s_data->s_error_log->column = i + 2;
		if (string[i] == STRING_CHAR)
		{
			buffer = find_second_quote(&string[i], fd);
			save_header(s_data, buffer, fd, type);
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
Read header information: .name and .comment
*/
void	read_header(int fd, t_data *s_data)
{
	char	*line;

	line = NULL;
	while (get_next_line(fd, &line))
	{
		ft_replace(&line, '\n', '\0');
		s_data->s_error_log->column = 1;
		if (*line != '\0')
			seek_header_char(s_data, line, fd);
		if (s_data->s_header->name_saved && s_data->s_header->comment_saved)
			break;
		// {
			// free(line);
			// return ;
		// }
		free(line);
		s_data->s_error_log->line += 1;
	}
	free(line);
	if (!s_data->s_header->name_saved || !s_data->s_header->comment_saved)
		lexical_error(s_data);
}
