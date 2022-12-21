/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 11:33:51 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/15 11:33:53 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
Takes error_msg as a parameter and puts that error_msg to stderr stream.
*/
void	ft_puterror(char *error_msg)
{
	if (error_msg == NULL)
		return ;
	while (*error_msg)
	{
		write(2, &(*error_msg), 1);
		error_msg++;
	}
}
