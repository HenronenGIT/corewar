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

// t_data_cell	*allocate_data_cell()
// {
// 	t_data_cell	*data_cell;

// 	data_cell = (t_data_cell *)malloc(sizeof(t_data_cell));
// 	if (!data_cell)
// 		error(MALLOC_ERR);
// 	data_cell->arg_1 = NULL;
// 	data_cell->arg_2 = NULL;
// 	data_cell->arg_3 = NULL;
// 	data_cell->byte_size = 0;
// 	data_cell->arg_1_size = 0;
// 	data_cell->arg_2_size = 0;
// 	data_cell->arg_3_size = 0;
// 	data_cell->arg_1_type = 0;
// 	data_cell->arg_2_type = 0;
// 	data_cell->arg_3_type = 0;
// 	data_cell->statement_code = NULL;
// 	data_cell->argument_type_code = NULL;
// 	data_cell->arg_1_hex = NULL;
// 	data_cell->arg_2_hex = NULL;
// 	data_cell->arg_3_hex = NULL;
// 	data_cell->final = NULL;
// 	return (data_cell);
// }

t_token	*allocate_token_struct(t_type type, char *content)
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
	t_token	*s_token;

	s_token = NULL;
	s_token = allocate_token_struct(type, sub_string);
	vec_insert(s_data->vec_tokens, s_token);

}

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
		if (is_delimiter(line[right]) == false)
			right += 1;
		if (is_delimiter(line[right]) == true && is_delimiter(line[left]) == true)
		{
			right += 1;
			left += 1;
		}
		else if ((is_delimiter(line[right]) == true && left != right) || (right == len && len && left != right))
		{
			sub_string = ft_strsub(line, left, right - left);
			if (!sub_string)
				error(MALLOC_ERR);
			if (is_statement(sub_string))
				save_token(s_data, sub_string, STATEMENT);
			else if (is_label(sub_string, s_data))
				save_token(s_data, sub_string, LABEL);
			left = right;
		}
	}
}

/*
Opens file descriptor for input reading.
After that while loops starts reading file descriptor line by line.
Every single line is sent to lexical_scanner function to be tokenized.
*/
void read_input(char *input, t_data *s_data)
{
	int fd;
	char *line;

	fd = 0;
	fd = open(input, O_RDONLY);
	if (fd == -1)
		error(OPEN_ERR);
	read_header(fd, s_data);
	while (get_next_line(fd, &line) != 0)
	{
		lexical_scanner(line, s_data);
		free(line);
	}
}
