/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:39:20 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/22 10:39:21 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
*/
static void	save_argument(t_stmnt **statement, t_token *token)
{
	(*statement)->args[(*statement)->arg_count] = token->content;
	if (token->type == REGISTER)
		(*statement)->arg_type[(*statement)->arg_count] = T_REG;
	else if (token->type == DIRECT || token->type == DIRECT_LABEL)
		(*statement)->arg_type[(*statement)->arg_count] = T_DIR;
	else if (token->type == INDIRECT)
		(*statement)->arg_type[(*statement)->arg_count] = T_IND;
	(*statement)->arg_count += 1;
}

static void	insert_arguments(t_data *s_data, t_token *token, t_type last_token)
{
	size_t	newest_element;
	t_stmnt	**input_array;

	if (last_token != SEPARATOR && last_token != INSTRUCTION)
		syntax_error(MISSING_COMMA_ERR, s_data->s_error_log, NULL, NULL);
	input_array = (t_stmnt **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	save_argument(&input_array[newest_element], token);
}

static void	allocate_element(t_data *s_data, t_token *token)
{
	t_stmnt	*element;
	int		op_code;

	element = (t_stmnt *)malloc(sizeof(t_stmnt));
	if (!element)
		error(MALLOC_ERR);
	element = init_values(element);
	if (token->type == LABEL)
		element->label_name = token->content;
	else
	{
		op_code = lookup(token->content);
		element->op_code = g_op_tab[op_code - 1].op_code;
	}
	vec_insert(s_data->vec_input, element);
}

void	syntax_analyzer(t_data *s_data)
{
	t_token			**tokens;
	static t_type	last_token;
	size_t			i;

	last_token = NEWLINE;
	tokens = (t_token **)s_data->vec_tokens->array;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == NEWLINE)
			validate_syntax(s_data, tokens[i], last_token);
		else if (tokens[i]->type == LABEL) //? check last element that it is newline
			allocate_element(s_data, tokens[i]);
		else if (tokens[i]->type == INSTRUCTION
			&& (last_token == LABEL || last_token == NEWLINE))
			allocate_element(s_data, tokens[i]);
		else if (tokens[i]->type == SEPARATOR && !is_argument(last_token))
			syntax_error(MISSING_COMMA_ERR, NULL, NULL, NULL);
		else if (is_argument(tokens[i]->type))
			insert_arguments(s_data, tokens[i], last_token);
		last_token = tokens[i]->type;
		i += 1;
	}
	if (last_token != NEWLINE)
		error(NO_NL_ERR);
}
