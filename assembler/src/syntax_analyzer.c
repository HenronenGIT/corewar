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

int lookup(const char *string)
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
void save_argument(t_input **input_array, t_token *token)
{
	size_t i;

	i = 0;
	while ((*input_array)->args[i] != NULL)
		i += 1;
	if (i >= 3)
		error(SYNTAX_ERROR);
	else
		(*input_array)->arg_count = i + 1;
	(*input_array)->args[i] = token->content;
	i = 0;
	while ((*input_array)->arg_type[i] != 0)
		i += 1;
	if (token->type == REGISTER)
		(*input_array)->arg_type[i] = T_REG;
	else if (token->type == DIRECT || token->type == DIRECT_LABEL)
		(*input_array)->arg_type[i] = T_DIR;
	else if (token->type == INDIRECT)
		(*input_array)->arg_type[i] = T_IND;
}

static void insert_arguments(t_data *s_data, t_token *token)
{
	size_t newest_element;
	t_input **input_array;

	input_array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	// if (token->type == SEPARATOR)
		// input_array[newest_element]->commas += 1;
	// else
		save_argument(&input_array[newest_element], token); // save argumnets better name?
}

static void validate_arg_types(t_input *cur_element, int op_code)
{
	int result;
	int	i;
	int *arg_type;

	i = 0;
	result = 0;
	arg_type = cur_element->arg_type;
	while (arg_type[i])
	{

	if (g_op_tab[op_code - 1].arg_type[i] && !arg_type[i])
		syntax_error(TEMP_ERR, cur_element, NULL);
		// return (0);
	result = arg_type[i] & g_op_tab[op_code - 1].arg_type[i];
	if (result != arg_type[i])
		syntax_error(INVALID_ARG_ERR, cur_element, NULL);
		i += 1;
	}
}

void validate_instruction_syntax(t_input *cur_element, t_token *cur_token)
{
	int op_code;
	size_t i;

	i = 0;
	op_code = cur_element->op_code;
	if (cur_element->arg_count != g_op_tab[op_code - 1].expected_arg_count)
		syntax_error(ARG_COUNT_ERR, cur_element, NULL);
	validate_arg_types(cur_element, op_code);
}

static void validate_label_syntax(t_input *cur_element, t_token *cur_token)
{
	if (cur_token->type != NEWLINE)
		syntax_error(NO_NL_ERR, NULL, cur_element->label_name);
}

static void validate_syntax(t_vec *vec_input, t_token *current_token, t_type last_token)
{
	t_input *newest_element;

	if (vec_input->space_taken == 0)
		return ;
	if (last_token == SEPARATOR) //Syntax error at token [TOKEN][004:016] ENDLINE
		syntax_error(NO_NL_ERR, NULL, NULL);
	newest_element = vec_input->array[vec_input->space_taken - 1];
	if (newest_element->label_name)
		validate_label_syntax(newest_element, current_token);
	else
		validate_instruction_syntax(newest_element, current_token);
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
	t_token **tokens = (t_token **)s_data->vec_tokens->array;
	static t_type last_token;
	size_t i;

	last_token = NEWLINE;
	i = 0;
	while (tokens[i])
	{
		if (tokens[i]->type == LABEL)
			allocate_element(s_data, tokens[i]);
		// else if ((tokens[i]->type == INSTRUCTION) && last_token != NEWLINE)
			// syntax_error(NO_NL_ERR, NULL, NULL);


			/* Upper statement is cleaner, is there better way to check that
				IF token is instruction, last token needs to be newline or label*/


		else if (tokens[i]->type == INSTRUCTION) //? This could be cleaner
		{
			if (last_token != NEWLINE && last_token != LABEL)
				syntax_error(NO_NL_ERR, NULL, NULL);
			else
				allocate_element(s_data, tokens[i]);
		}
		// else if (tokens[i]->type == INSTRUCTION)
			// allocate_element(s_data, tokens[i]);
		else if (tokens[i]->type == NEWLINE)
			validate_syntax(s_data->vec_input, tokens[i], last_token);
		else if (tokens[i]->type == SEPARATOR && !is_argument(last_token))
			syntax_error(MISSING_COMMA_ERR, NULL, NULL);
		else if (is_argument(tokens[i]->type))
			insert_arguments(s_data, tokens[i]);
		last_token = tokens[i]->type;
		i += 1;
	}
	if (last_token != NEWLINE)
		syntax_error(NO_NL_ERR, NULL, NULL); //Syntax error at token [TOKEN][005:007] END "(null)"
}
