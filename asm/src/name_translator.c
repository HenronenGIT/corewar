/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   name_translator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 11:23:23 by okoponen          #+#    #+#             */
/*   Updated: 2022/11/24 11:23:24 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

<<<<<<< HEAD
char	*name_translator(t_header *name)
{
	int		i;
	int		j;
	char	*name_str;
	char	*magic;
	char	*temp;

	i = 0;
	j = 0;
	name_str = (char *)malloc(sizeof(char) * (PROG_NAME_LENGTH * 2 + 1));
	if (!name_str)
		exit (0);
	name_str[PROG_NAME_LENGTH * 2] = '\0';
	magic = ft_strdup("0xea83f");
	while (magic[j])
		name_str[i++] = magic[j++];
	j = 0;
	while (name->prog_name[j])
	{
		temp = ft_itoh((int)name->prog_name[j], 1);
		name_str = ft_strcat(name_str, temp);
		free(temp);
		j++;
		i += 2;
	}
	while (j < PROG_NAME_LENGTH * 2)
	{
		name_str = ft_strcat(name_str, "0");
		i += 2;
	}
	free(magic);
	return (name_str);
}
=======
// void	name_translator()
>>>>>>> 3f373b85590e3024da301092b028b0d1a7f19d61
