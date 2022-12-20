/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 15:22:52 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/11 15:22:52 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static t_token	*allocate_token_struct(t_type type, char *content)
{
	t_token	*s_token;

	s_token = (t_token *)malloc(sizeof(t_token));
	if (!s_token)
		error(MALLOC_ERR);
	s_token->type = type;
	s_token->content = content;
	return (s_token);
}

static void	save_token(t_data *s_data, char *sub_string, t_type type)
{
	t_token	*s_token;

	s_token = NULL;
	s_token = allocate_token_struct(type, sub_string);
	vec_insert(s_data->vec_tokens, s_token);
}

static	void	validate_statement(t_data *s_data, char *sub_string)
{
	if (!sub_string)
		error(MALLOC_ERR);
	if (is_label(s_data, sub_string))
		save_token(s_data, sub_string, LABEL);
	else if (is_statement(sub_string))
		save_token(s_data, sub_string, INSTRUCTION);
	else if (is_directlabel(s_data, sub_string))
		save_token(s_data, sub_string, DIRECT_LABEL);
	else if (is_direct(s_data, sub_string))
		save_token(s_data, sub_string, DIRECT);
	else if (is_indirect(s_data, sub_string))
		save_token(s_data, sub_string, INDIRECT);
	else if (is_register(sub_string))
		save_token(s_data, sub_string, REGISTER);
	else
		lexical_error(s_data);
}

/*
Receives "line" as a parameter.
lexical_scanner iterates "line" byte by byte and tries to search tokens.
When lexical analysis finds string literal
that matches to one of the types of token, 
it saves that to token to "t_token" struct.
*/
//! TOKEN LOCATION CAN BE SAVED. ADD TO SAVE_TOKEN FUNCTION.
void	lexical_scanner(char *line, t_data *s_data)
{
	unsigned int	left;
	unsigned int	right;

	left = 0;
	right = 0;
	while (line[right])
	{
		s_data->s_error_log->column = right + 1;
		if (line[right] == COMMENT_CHAR && left == right)
			break ;
		if (is_separator(line[right]) && left == right)
			save_token(s_data, ft_strsub(&line[left], 0, 1), SEPARATOR);
		if (is_delim(line[right]) == false)
			right += 1;
		if (is_delim(line[right]) == true && is_delim(line[left]) == true)
		{
			right += 1;
			left += 1;
		}
		else if (is_delim(line[right]) == true && left != right)
		{
			validate_statement(s_data, ft_strsub(line, left, right - left));
			left = right;
		}
	}
}

/*
Opens file descriptor for reading the input.
After that while loops starts reading file descriptor line by line.
Every single line is sent to lexical_scanner function to be tokenized.
*/
void	tokenization(char *input, t_data *s_data)
{
	int		fd;
	char	*line;
	int		had_newline;

	had_newline = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd, s_data);
	while (get_next_line(fd, &line) != 0)
	{
		had_newline = 0;
		if (ft_replace(&line, '\n', '\0'))
			had_newline = 1;
		lexical_scanner(line, s_data);
		if (had_newline)
			save_token(s_data, "\n", NEWLINE);
		free(line);
		s_data->s_error_log->line += 1;
	}
	close(fd);
}
