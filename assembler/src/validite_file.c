/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validite_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:24:00 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/14 16:24:01 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	validate_file(char *file_name)
{
	char	*dot;

	dot = ft_strrchr(file_name, '.');
	if (!dot)
		error(INVALID_FILE_NAME_ERR);
	if (ft_strncmp(dot, ".s", 3) != 0)
		error(INVALID_FILE_NAME_ERR);
}
