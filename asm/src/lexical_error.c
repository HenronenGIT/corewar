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
void	lexical_error(t_data *s_data, char *line, int error_number)
{
	//temp... make analysis to the line and find in whiich column error was
	if (error_number == TEMP_ERR)
		error(TEMP_ERR);
	else if (error_number == NAME_ERR)
		error(TEMP_ERR);
}