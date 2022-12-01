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

t_token *allocate_token_struct(t_type type, char *content)
{
	t_token *s_token;

	s_token = (t_token *)malloc(sizeof(t_token));
	if (!s_token)
		error(MALLOC_ERR);
	s_token->type = type;
	s_token->content = content;
	return (s_token);
}

void save_token(t_data *s_data, char *sub_string, t_type type)
{
	t_token *s_token;

	s_token = NULL;
	s_token = allocate_token_struct(type, sub_string);
	vec_insert(s_data->vec_tokens, s_token);
	// print_tokens(s_data->vec_tokens);
}

/*
Receives "line" as a parameter.
lexical_scanner iterates what "line" byte by byte and tries to search tokens.
When lexical analysis find string literal that matches to one of the types of token,
it saves that to token to "t_token" struct.
*/
void lexical_scanner(char *line, t_data *s_data)
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
		s_data->s_error_log->column = left + 1;
		if (line[right] == COMMENT_CHAR)
			break;
		if (is_separator(line[right]) && left == right)
			save_token(s_data, ft_strsub(&line[left], 0, 1), SEPARATOR);
		if (is_delimiter(line[right]) == false)
			right += 1;
		if (is_delimiter(line[right]) == true && is_delimiter(line[left]) == true)
		{
			right += 1;
			left += 1;
		}

		// mayby can be splitted over here to separate function
		else if (is_delimiter(line[right]) == true && left != right)
		{
			sub_string = ft_strsub(line, left, right - left);
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
				save_token(s_data, sub_string, INVALID);
			left = right;
		}
	}
}

/*
Opens file descriptor for reading the input.
After that while loops starts reading file descriptor line by line.
Every single line is sent to lexical_scanner function to be tokenized.
*/
void	read_input(char *input, t_data *s_data)
{
	int		fd;
	char	*line;

	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd, s_data);
	while (get_next_line(fd, &line) != 0)
	{
		lexical_scanner(line, s_data);
		free(line);
		s_data->s_error_log->line += 1;
	}
}
