/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 17:19:10 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/30 17:21:00 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_word_count(const char *s, char c)
{
	size_t	i;
	int		is_word;
	size_t	word_count;

	i = 0;
	word_count = 0;
	is_word = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && is_word == 0)
		{
			is_word = 1;
			word_count++;
		}
		if (s[i] == c)
			is_word = 0;
		i++;
	}
	return (word_count);
}
