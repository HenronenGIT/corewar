/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_syntax.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:17:37 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/21 13:17:39 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	validate_arg_types(t_data *s_data, t_input *cur_element)
{
	int			result;
	int			*arg_type;
	const char	*instruction;
	int			op_code;
	int			i;

	op_code = cur_element->op_code;
	instruction = g_op_tab[op_code - 1].instruction;
	i = 0;
	result = 0;
	arg_type = cur_element->arg_type;
	while (arg_type[i])
	{
		if (g_op_tab[op_code - 1].arg_type[i] && !arg_type[i])
			syntax_error(ARG_ERR, s_data->s_error_log, NULL, NULL);
		result = arg_type[i] & g_op_tab[op_code - 1].arg_type[i];
		if (result != arg_type[i])
			syntax_error(ARG_ERR, s_data->s_error_log, instruction, NULL);
		i += 1;
	}
}

void	validate_instruction(t_data *s_data, t_input *element, t_token *token)
{
	int			op_code;
	const char	*instruction;

	instruction = g_op_tab[element->op_code - 1].instruction;
	op_code = element->op_code;
	if (element->arg_count != g_op_tab[op_code - 1].expected_arg_count)
		syntax_error(ARG_COUNT_ERR, s_data->s_error_log, instruction, token);
	validate_arg_types(s_data, element);
}

static void	validate_label(t_input *cur_element, t_token *cur_token)
{
	if (cur_token->type != NEWLINE)
		syntax_error(NO_NL_ERR, NULL, cur_element->label_name, NULL);
}

void	validate_syntax(t_data *s_data, t_token *cur_token, t_type last_token)
{
	t_input	*newest_element;
	t_vec	*vec_input;

	vec_input = s_data->vec_input;
	if (vec_input->space_taken == 0)
		return ;
	if (last_token == SEPARATOR)
		syntax_error(INVALID_EOL_ERR, NULL, NULL, cur_token);
	newest_element = s_data->vec_input->array[vec_input->space_taken - 1];
	if (newest_element->label_name)
		validate_label(newest_element, cur_token);
	else
		validate_instruction(s_data, newest_element, cur_token);
	return ;
}
