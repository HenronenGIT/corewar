/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:43:32 by okoponen          #+#    #+#             */
/*   Updated: 2022/12/20 13:43:37 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	free_s_data_cell(t_input *cell)
{
	if (cell->label_name)
		free(cell->label_name);
	if (cell->final)
		free (cell->final);
}

void	free_t_vec(t_vec *s_vec)
{
	int	i;

	i = 0;
	while (s_vec->array[i])
	{
		free_s_data_cell(s_vec->array[i]);
		i++;
	}
	free(s_vec);
}
