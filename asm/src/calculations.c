/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculations.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:37:37 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/29 13:37:38 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static int fetch_size(int arg_type, int op_code)
{
	if (arg_type == T_REG)
		return (T_REG_SIZE);
	else if (arg_type == T_IND)
		return (T_IND_SIZE);
	else if (arg_type == T_DIR)
		return (g_table[op_code - 1].direct_size);
	else
		return (0);
}

static int calculate_total(t_input *statement)
{
	int sum;
	int i;

	i = -1;
	sum = 0;
	sum += STATEMENT_SIZE;
	while (statement->arg_size[++i] != 0)
		sum += statement->arg_size[i];
	if (g_table[statement->op_code - 1].arg_type_code)
		sum += 1;
	return (sum);
}

static void calculate_bytes(t_input *statement)
{
	static int total_bytes;
	int i;

	i = -1;
	statement->current_bytes = total_bytes;
	while (statement->arg_type[++i])
		statement->arg_size[i] = fetch_size(statement->arg_type[i], statement->op_code);
	if (statement->label_name == NULL)
		statement->total_size = calculate_total(statement);
	total_bytes += statement->total_size;
}

void calculate_statement_sizes(t_data *s_data)
{
	t_input **ptr;
	size_t	last_element;

	last_element = s_data->vec_input->space_taken - 1;
	ptr = (t_input **)s_data->vec_input->array;
	while (*ptr != NULL)
	{
		calculate_bytes(*ptr);
		ptr += 1;
	}
	ptr -= 1;
	s_data->champ_size = (*ptr)->current_bytes + (*ptr)->total_size;
}
