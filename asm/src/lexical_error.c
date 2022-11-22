/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexical_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:20:46 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/14 15:20:47 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

/*
Output error messages, and specify in which line that error happened.
*/
void	lexical_error(t_data *s_data, int error_number)
{
	size_t	line_count;
	size_t	column_count;

	line_count = s_data->s_error_log->line;
	column_count = s_data->s_error_log->column;
	ft_printf("Lexical error at [%d:%d]\n", line_count, column_count);
	if (error_number == TEMP_ERR)
		error(TEMP_ERR);
	else if (error_number == NAME_ERR)
		error(TEMP_ERR);
}
