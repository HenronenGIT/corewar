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

static int contains_invalid_characters(t_data *s_data, char *string)
{
	while (*string != ':')
	{
		if (ft_strchr(LABEL_CHARS, *string) == NULL)
			return (-1);
		string += 1;
	}
	return (0);
}

/*
Validates if string literal matches specifications of LABEL.
*/
bool is_label(char *sub_string, t_data *s_data)
{
	char *found_colon;

	found_colon = NULL;
	found_colon = ft_strchr(sub_string, LABEL_CHAR);
	if (found_colon == NULL)
		return (false);
	if (*(found_colon + 1) != '\0')
		return (false);
	if (contains_invalid_characters(s_data, sub_string))
		lexical_error(s_data, NULL, TEMP_ERR);
	return (true);
}

bool is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == SEPARATOR_CHAR || c == '\0')
		return (true);
	return (false);
}

bool is_statement(char *sub_string)
{
	if (!ft_strcmp(sub_string, "live") || !ft_strcmp(sub_string, "ld") || !ft_strcmp(sub_string, "st") || !ft_strcmp(sub_string, "add") || !ft_strcmp(sub_string, "sub") || !ft_strcmp(sub_string, "and") || !ft_strcmp(sub_string, "or") || !ft_strcmp(sub_string, "xor") || !ft_strcmp(sub_string, "zjmp") || !ft_strcmp(sub_string, "ldi") || !ft_strcmp(sub_string, "sti") || !ft_strcmp(sub_string, "fork") || !ft_strcmp(sub_string, "lld") || !ft_strcmp(sub_string, "lldi") || !ft_strcmp(sub_string, "lfork") || !ft_strcmp(sub_string, "aff"))
		return (1);
	return (0);
}

bool is_register(char *string)
{
	size_t i;

	if (string[0] != REGISTER_CHAR)
		return (false);
	i = 1;
	while (string[i] != '\0')
	{
		if (!ft_isdigit(string[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool is_separator(char c)
{
	if (c == SEPARATOR_CHAR)
		return (true);
	return (false);
}

bool is_directlabel(char *string)
{
	if (string[0] != DIRECT_CHAR)
		return (false);
	if (string[1] != LABEL_CHAR)
		return (false);
	return (true);
}

bool is_direct(t_data *s_data, char *string)
{
	size_t i;

	i = 2;
	if (string[0] != DIRECT_CHAR)
		return (false);
	if (string[1] == LABEL_CHAR)
		return (false);
	while (string[i] != '\0')
	{
		if (ft_strchr(LABEL_CHARS, string[i]) == NULL)
			lexical_error(s_data, NULL, TEMP_ERR);
		i += 1;
	}
	return (true);
}
