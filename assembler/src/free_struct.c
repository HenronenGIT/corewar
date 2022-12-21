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
	int	i;

	i = 0;
	if (cell->final)
		free (cell->final);
	// while (i <= 3)
	// {
	// 	if (cell->args[i])
	// 		free(cell->args[i]);
	// 	i++;
	// }
	free(cell);
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
	// free(s_vec);
}

void	free_tokens(t_vec *vec_token)
{
	int		i;
	t_token	**array;

	i = 0;
	array = (t_token **)vec_token->array;
	while (array[i])
	{
		printf("array->content:%s\n", array[i]->content);
		// exit(1);
		if (array[i]->content[0] != '\n')
			free(array[i]->content);
		free(array[i]);
		i++;
	}
	// free(vec_token);
}
