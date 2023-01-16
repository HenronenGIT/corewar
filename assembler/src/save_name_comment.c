/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_name_comment.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 14:58:33 by hmaronen          #+#    #+#             */
/*   Updated: 2023/01/12 14:58:34 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Function that iterates trough strubg untils finds ending quote.
During iteration saves all bytes to s_header struct.
*/
void	save_header(t_data *s_data, char *buffer, t_type type)
{
	char	*dst;

	dst = decide_destination(s_data, type);
	ft_strcpy(dst, buffer);
	if (type == NAME && ft_strlen(dst) > PROG_NAME_LENGTH)
		error(NAME_LEN_ERR);
	else if (type == COMMENT && ft_strlen(dst) > COMMENT_LENGTH)
		error(COMMENT_LEN_ERR);
}

static void	append_to_buffer(char **buffer, char *line, int len)
{
	char	*temp;

	temp = NULL;
	temp = ft_strsub(line, 0, len);
	ft_realloc(buffer, temp);
	free(temp);
}

static char	*find_second_quote(t_data *s_data, char *string, int fd)
{
	char	*buffer;
	char	*line;
	char	*second_quote;

	second_quote = NULL;
	line = NULL;
	buffer = ft_strdup(&string[1]);
	while (get_next_line(fd, &line))
	{
		second_quote = ft_strchr(line, STRING_CHAR);
		if (second_quote - line == 0)
			break ;
		else if (second_quote)
		{
			append_to_buffer(&buffer, line, second_quote - line);
			break ;
		}
		else
			ft_realloc(&buffer, line);
		ft_strdel(&line);
	}
	reel_to_end(s_data, second_quote);
	if (line)
		free(line);
	return (buffer);
}

char	*save_to_buffer(t_data *s_data, char *string, int fd)
{
	char	*buffer;
	char	*second_quote;

	second_quote = ft_strchr(&string[1], STRING_CHAR);
	if (second_quote)
	{
		reel_to_end(s_data, second_quote + 1);
		return (ft_strsub(string, 1, second_quote - string - 1));
	}
	else
		buffer = find_second_quote(s_data, string, fd);
	return (buffer);
}
