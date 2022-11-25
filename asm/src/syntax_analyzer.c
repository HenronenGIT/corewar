
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

static t_input *init_values(t_input *element)
{
	element->is_label = false;
	element->instruction = 0;
	element->args[0] = NULL;
	element->args[1] = NULL;
	element->args[2] = NULL;
	element->args[3] = NULL;
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

static void init_instruction(t_data *s_data, t_token *token)
{
	size_t newest_element;

	newest_element = s_data->vec_tokens->space_taken - 1;
}

static void init_label(t_data *s_data, t_token *token)
{
	size_t newest_element;
	t_input **input_array;
	t_input *element;
	t_input	**array;

	array = (t_input **)s_data->vec_input->array;
	newest_element = s_data->vec_input->space_taken - 1;
	// s_data->vec_input->array[newest_element]->label_name = token->content;
	array[newest_element]->label_name = token->content;
	// 1
	// input_array = (t_input **)s_data->vec_input->array;
	// newest_element = s_data->vec_input->space_taken - 1;
	// input_array[newest_element]->label_name = token->content;

	// 2
	// newest_element = s_data->vec_input->space_taken - 1;
	// element = s_data->vec_input->array[newest_element];
	// element->label_name = ft_strdup(token->content);
	// s_data->vec_input->array[newest_element] = element;
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
	// t_input **input_array = (t_input **)s_data->vec_input->array;
	t_vec *vec_tokens = s_data->vec_tokens;
	size_t i;

	i = 0;
	while (i < vec_tokens->space_taken)
	{
		if (token_array[i]->type == LABEL || token_array[i]->type == INSTRUCTION)
			allocate_element(s_data);
		if (token_array[i]->type == LABEL)
			init_label(s_data, token_array[i]);
		else
			init_instruction(s_data, token_array[i]);
		i += 1;
	}
	//? Check valid syntax after every init?
	//? Or check syntax after all inits are done.
}