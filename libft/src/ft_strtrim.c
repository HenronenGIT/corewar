/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 13:37:13 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/22 12:43:05 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s)
{
	char	*new_str;
	int		i;
	int		start;
	int		end;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] == ' ' || s[i] == 9 || s[i] == 10 || s[i] == ',')
		i++;
	if (s[i] == 0)
		return (new_str = ft_strnew(0));
	start = i;
	while (s[i] != 0)
		i++;
	while (s[i] == ' ' || s[i] == 9 || s[i] == 10 || s[i] == ',' || s[i] == 0)
		i--;
	end = i;
	i = 0;
	new_str = ft_strnew(end - start + 1);
	if (new_str == 0)
		return (NULL);
	while (start++ <= end && i++ >= 0)
		new_str[i - 1] = s[start - 1];
	return (new_str);
}
