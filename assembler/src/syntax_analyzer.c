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

int	lookup(const char *string)
{
	size_t i;

	i = 0;
	while (g_op_tab[i].instruction != NULL)
	{
		if (ft_strcmp(string, g_op_tab[i].instruction) == 0)
			return (g_op_tab[i].op_code);
		i += 1;
	}
	return (-1);
}

/*
Fill argument values to...
*/
void	save_argument(t_input **statement, t_token *token)
{
	if ((*statement)->arg_count > 3)
		syntax_error(TOO_MANY_ARG_ERR, NULL, NULL, NULL);
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
	t_input	**input_array;

	if (last_token != SEPARATOR && last_token != INSTRUCTION)
		syntax_error(MISSING_COMMA_ERR, s_data->s_error_log, NULL, NULL);
	input_array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	save_argument(&input_array[newest_element], token); // save argumnets better name?
}

static void	validate_arg_types(t_data *s_data, t_input *cur_element, int op_code)
{
	int	result;
	int	i;
	int	*arg_type;
	const char *instruction;

	instruction = g_op_tab[op_code - 1].instruction;
	i = 0;
	result = 0;
	arg_type = cur_element->arg_type;
	while (arg_type[i])
	{
		if (g_op_tab[op_code - 1].arg_type[i] && !arg_type[i])
			syntax_error(TEMP_ERR,NULL, NULL, NULL);
		result = arg_type[i] & g_op_tab[op_code - 1].arg_type[i];
		if (result != arg_type[i])
			syntax_error(INVALID_ARG_ERR, s_data->s_error_log, instruction, NULL);
		i += 1;
	}
}

void	validate_instruction_syntax(t_data *s_data, t_input *cur_element, t_token *cur_token)
{
	int op_code;
	const char	*instruction;

	instruction = g_op_tab[cur_element->op_code - 1].instruction;
	op_code = cur_element->op_code;
	if (cur_element->arg_count != g_op_tab[op_code - 1].expected_arg_count)
		syntax_error(ARG_COUNT_ERR, s_data->s_error_log, instruction, cur_token);
	validate_arg_types(s_data, cur_element, op_code);
}

static void	validate_label_syntax(t_input *cur_element, t_token *cur_token)
{
	if (cur_token->type != NEWLINE)
		syntax_error(NO_NL_ERR, NULL, cur_element->label_name, NULL);
}

// static void validate_syntax(t_vec *vec_input, t_token *current_token, t_type last_token)
static void validate_syntax(t_data *s_data, t_token *current_token, t_type last_token)
{
	t_input *newest_element;
	t_vec	*vec_input;

	vec_input = s_data->vec_input;
	if (vec_input->space_taken == 0)
		return ;
	if (last_token == SEPARATOR) //Syntax error at token [TOKEN][004:016] ENDLINE
		syntax_error(INVALID_EOL_ERR, NULL, NULL, current_token);
	newest_element = s_data->vec_input->array[vec_input->space_taken - 1];
	if (newest_element->label_name)
		validate_label_syntax(newest_element, current_token);
	else
		validate_instruction_syntax(s_data, newest_element, current_token);
	return;
}

static void allocate_element(t_data *s_data, t_token *token)
{
	t_input *element;
	int op_code;

	element = (t_input *)malloc(sizeof(t_input));
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

void syntax_analyzer(t_data *s_data)
{
	t_token			**tokens;
	static t_type	last_token;
	size_t			i;

	last_token = NEWLINE;
	tokens = (t_token **)s_data->vec_tokens->array;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == LABEL)//? check last element that it is newline?
			allocate_element(s_data, tokens[i]);
		if ( tokens[i]->type == INSTRUCTION
			&& (last_token == LABEL || last_token == NEWLINE))
			allocate_element(s_data, tokens[i]);
		if (tokens[i]->type == NEWLINE)
			validate_syntax(s_data, tokens[i], last_token);
		else if (tokens[i]->type == SEPARATOR && !is_argument(last_token))
			syntax_error(MISSING_COMMA_ERR, NULL, NULL, NULL);
		else if (is_argument(tokens[i]->type))
			insert_arguments(s_data, tokens[i], last_token);
		last_token = tokens[i]->type;
		i += 1;
	}
	if (last_token != NEWLINE)
		syntax_error(NO_NL_ERR, NULL, NULL, NULL); //Syntax error at token [TOKEN][005:007] END "(null)"
}