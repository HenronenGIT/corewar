
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

	// printf("%d\n", g_table[2].params_type[0]);
	// printf("%d\n", g_table[2].params_type[1]);
	// printf("%d\n", g_table[2].params_type[2]);
	// exit(0);
	while (g_table[i].instruction != NULL)
	{
		if (ft_strcmp(string, g_table[i].instruction) == 0)
			return (g_table[i].op_code);
		i += 1;
	}
	return (-1);

	// 	t_op op_tab[17] =
	// 		{
	// 			{"live", 1, {T_DIR}},
	// 			{"ld", 2, {T_DIR | T_IND, T_REG}},
	// 			{"st", 3, {T_REG, T_IND | T_REG}},
	// 			{"add", 4, {T_REG, T_REG, T_REG}},
	// 			{"sub", 5, {T_REG, T_REG, T_REG}},
	// 			{"and", 6, {T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG}},
	// 			{"or", 7, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	// 			{"xor", 8, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}},
	// 			{"zjmp", 9, {T_DIR}},
	// 			{"ldi", 10, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	// 			{"sti", 11, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}},
	// 			{"fork", 12, {T_DIR}},
	// 			{"lld", 13, {T_DIR | T_IND, T_REG}},
	// 			{"lldi", 14, {T_REG | T_DIR | T_IND, T_DIR | T_REG, T_REG}},
	// 			{"lfork", 15, {T_DIR}},
	// 			{"aff", 16, {T_REG}},
	// 			{0, 0, {0}}};
}

static t_input *init_values(t_input *element)
{
	element->op_code = 0;
	element->args[0] = NULL;
	element->args[1] = NULL;
	element->args[2] = NULL;
	element->args[3] = NULL;
	element->arg_type[0] = 0;
	element->arg_type[1] = 0;
	element->arg_type[2] = 0;
	element->arg_type[3] = 0;
	element->label_name = NULL;
	element->byte_size = 0;
	element->arg_size[0] = 0;
	element->arg_size[1] = 0;
	element->arg_size[2] = 0;
	element->arg_size[3] = 0;
	element->current_bytes = 0;
	element->argument_type_code = 0;
	element->arg_values[0] = 0;
	element->arg_values[1] = 0;
	element->arg_values[2] = 0;
	element->arg_values[3] = 0;
	element->final = NULL;
	return (element);
}

void save_argument(t_input **input_array, t_token *token)
{
	size_t	i;

	i = 0;
	while ((*input_array)->args[i] != NULL)
		i += 1;
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

static void init_instruction(t_data *s_data, t_token *token)
{
	size_t newest_element;
	t_input **input_array;

	if (token->type == SEPARATOR)
		return;
	input_array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	if (token->type == INSTRUCTION)
		input_array[newest_element]->op_code = lookup(token->content);
	else
		save_argument(&input_array[newest_element], token);
	// else if (input_array[newest_element]->args[0] == NULL)
	// 	input_array[newest_element]->args[0] = token->content;
	// else if (input_array[newest_element]->args[1] == NULL)
	// 	input_array[newest_element]->args[1] = token->content;
	// else if (input_array[newest_element]->args[2] == NULL)
	// 	input_array[newest_element]->args[2] = token->content;
}

static void init_label(t_data *s_data, t_token *token)
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
	// s_data->vec_input->array
	element = (t_input *)malloc(sizeof(t_input));
	if (!element)
		exit(MALLOC_ERR);
	element = init_values(element);
	vec_insert(s_data->vec_input, element);
}

/*
1. syntax_analyzer() function starts by allocating new t_input struct.
2. After allocation syntax_analyzer() starts iterating array found from:
	s_data->vec_tokens->array
3. Depending what is the type of that token found from that array, we init values
	to that new allocated struct.
*/
void syntax_analyzer(t_data *s_data)
{
	t_token **token_array = (t_token **)s_data->vec_tokens->array;
	t_vec *vec_tokens = s_data->vec_tokens;
	size_t i;

	i = 0;
	while (i < vec_tokens->space_taken)
	{
		if (token_array[i]->type == LABEL || token_array[i]->type == INSTRUCTION)
		{
			//validate_last struct
			allocate_element(s_data);
		}
		if (token_array[i]->type == LABEL)
			init_label(s_data, token_array[i]);
		else
			init_instruction(s_data, token_array[i]);
		i += 1;
	}
	//? Check valid syntax after every init?
	//? Or check syntax after all inits are done.
}