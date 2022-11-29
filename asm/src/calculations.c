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

static int fetch_size(int arg_type)
{
	if (arg_type == T_REG)
		return (T_REG_SIZE);
	else if (arg_type == T_IND)
		return (T_IND_SIZE);
	else
		return (0);
}

static void calculate_bytes(t_input *statement)
{
	static int total_bytes;

	if (statement->label_name)
	{
	}
	else
	{
		statement->current_bytes += 1;
		statement->arg_size[0] = fetch_size(statement->arg_type[0]);
		statement->arg_size[1] = fetch_size(statement->arg_type[1]);
		statement->arg_size[2] = fetch_size(statement->arg_type[2]);
	}

	// if (statement->label_name)
	// return ;

	// statement->current_bytes = 999;
}

void calculate_statement_sizes(t_vec *vec_statements)
{
	t_input **ptr;

	ptr = (t_input **)vec_statements->array;
	// while (vec_statements->space_taken)
	while (*ptr != NULL)
	{
		calculate_bytes(*ptr);
		ptr += 1;
	}

	// iterate trough vec_statements->array
	//
}
