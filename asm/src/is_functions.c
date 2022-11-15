/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:00:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/14 14:00:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

bool	is_delimiter(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

bool	is_statement(char *sub_string)
{
	if (ft_strcmp(sub_string, "live") || ft_strcmp(sub_string, "ld")
		|| ft_strcmp(sub_string, "st") || ft_strcmp(sub_string, "add")
		|| ft_strcmp(sub_string, "sub") || ft_strcmp(sub_string, "and")
		|| ft_strcmp(sub_string, "or") || ft_strcmp(sub_string, "xor")
		|| ft_strcmp(sub_string, "zjmp") || ft_strcmp(sub_string, "ldi")
		|| ft_strcmp(sub_string, "sti")|| ft_strcmp(sub_string, "fork")
		|| ft_strcmp(sub_string, "lld") || ft_strcmp(sub_string, "lldi")
		|| ft_strcmp(sub_string, "lfork") || ft_strcmp(sub_string, "aff"))
			return (1);
		return (0);
}

bool	is_label(char *sub_string, t_data *data)
{
	char	*found_char;

	found_char = NULL;
	found_char = ft_strchr(sub_string, LABEL_CHAR);
	if (found_char == NULL)
		return (false);
	if ((found_char + 1) != '\0')
		lexical_error(data);
	return (true);

}