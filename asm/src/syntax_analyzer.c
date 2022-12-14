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
	while (g_table[i].instruction != NULL)
	{
		if (ft_strcmp(string, g_table[i].instruction) == 0)
			return (g_table[i].op_code);
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

static void copy_instruction_data(t_data *s_data, t_token *token)
{
	size_t newest_element;
	t_input **input_array;

	// if (token->type == SEPARATOR)
	// return;
	input_array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	if (token->type == SEPARATOR)
		input_array[newest_element]->commas += 1;
	else if (token->type == INSTRUCTION)
		input_array[newest_element]->op_code = lookup(token->content);
	else
		save_argument(&input_array[newest_element], token); // save argumnets better name?
}

static void copy_label_data(t_data *s_data, t_token *token)
{
	size_t newest_element;
	t_input **array;

	array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	array[newest_element]->label_name = token->content;
}

/*
Allocates the new pointer that points to t_input struct.
After allocation vec_insert() function inserts that pointer to:
	 s_data->vec_tokens->array
*/
static void allocate_element(t_data *s_data)
{
	t_input *element;

	element = (t_input *)malloc(sizeof(t_input));
	if (!element)
		error(MALLOC_ERR);
	element = init_values(element);
	vec_insert(s_data->vec_input, element);
}

void validate_label_syntax(t_input *label_element)
{
	// if (label_element->)

	/* Need to check with different error files that what conditions we need
	to validate valid label element.

	Easy way out would be to just check every single variable that they are eiteher
	NULL or 0*/
}

void validate_instruction_syntax(t_input *statement)
{
	int op_code;
	int result;
	size_t i;

	i = 0;
	result = 0;
	op_code = statement->op_code;
	if ((statement->arg_count - statement->commas) != 1)
		error(MISSING_COMMA_ERR);
	while (i < 3)
	{
		if (g_table[op_code - 1].params_type[i] && !statement->arg_type[i])
			error(SYNTAX_ERROR);
		result = statement->arg_type[i] & g_table[op_code - 1].params_type[i];
		//! error here
		if (result != statement->arg_type[i])
			syntax_error(op_code, statement->arg_type[i]);
		// error(SYNTAX_ERROR);
		//
		i += 1;
	}
}

static void validate_syntax(t_vec *vec_input)
{
	t_input *statement;
	size_t newsest_element;

	newsest_element = vec_input->space_taken - 1;
	if (vec_input->space_taken == 0)
		return;
	statement = vec_input->array[newsest_element];
	// validate_label_syntax might NOT be needed... check with different error cases
	if (statement->label_name)
		validate_label_syntax(statement);
	else
		validate_instruction_syntax(statement);
}

/*
	Iterates trough dynamic array found from s_data->vec_tokens;
	If token found from array is LABEL or INSTRUCTION
		-> Validate syntax from last element.
		-> Allocate new element
	else
		-> Init data to the element that was allocated before
*/
void	syntax_analyzer(t_data *s_data)
{
	t_token	**tokens = (t_token **)s_data->vec_tokens->array;
	t_vec	*vec_tokens = s_data->vec_tokens;
	size_t	i;

	i = 0;
	while (vec_tokens->array[i])
	{
		if (tokens[i]->type == LABEL || tokens[i]->type == INSTRUCTION)
		{
			validate_syntax(s_data->vec_input);
			allocate_element(s_data);
		}
		if (tokens[i]->type == LABEL)
			copy_label_data(s_data, tokens[i]);
		else
			copy_instruction_data(s_data, tokens[i]);
		i += 1;
	}
	validate_syntax(s_data->vec_input); // better style?
}
