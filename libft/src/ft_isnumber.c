/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumber.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:12:30 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/15 15:12:33 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_isnumber(char *string)
{
	if (string == NULL || *string == '\0')
		return (0);
	if (*string == '-' && ft_isdigit(string[1]))
		string++;
	while (*string)
	{
		if (ft_isdigit(*string))
			string++;
		else
			return (0);
	}
	return (1);
}
