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

static int	fetch_size(int arg_type, int op_code)
{
	if (arg_type == T_REG)
		return (T_REG_SIZE);
	else if (arg_type == T_IND)
		return (T_IND_SIZE);
	else if (arg_type == T_DIR)
		return (g_op_tab[op_code - 1].direct_size);
	else
		return (0);
}

static int	calculate_total(t_statement *statement)
{
	int	sum;
	int	i;

	i = -1;
	sum = 0;
	sum += STATEMENT_SIZE;
	while (statement->arg_size[++i] != 0)
		sum += statement->arg_size[i];
	if (g_op_tab[statement->op_code - 1].arg_type_code)
		sum += 1;
	return (sum);
}

static void	calculate_bytes(t_statement *stmnt)
{
	static int	total_bytes;
	int			i;

	i = -1;
	stmnt->current_bytes = total_bytes;
	while (stmnt->arg_type[++i])
		stmnt->arg_size[i] = fetch_size(stmnt->arg_type[i], stmnt->op_code);
	if (stmnt->label_name == NULL)
		stmnt->total_size = calculate_total(stmnt);
	total_bytes += stmnt->total_size;
}

void	calculate_statement_sizes(t_data *s_data)
{
	t_statement	**arr;
	size_t		i;
	size_t		last_i;

	i = 0;
	last_i = s_data->vec_input->space_taken - 1;
	arr = (t_statement **)s_data->vec_input->array;
	if (arr[i] == NULL)
		error(MISSING_CHAMP_ERR);
	while (arr[i])
	{
		calculate_bytes(arr[i]);
		i += 1;
	}
	s_data->champ_size = arr[last_i]->current_bytes + arr[last_i]->total_size;
}
