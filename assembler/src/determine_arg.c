/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:00:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/14 14:00:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

bool	is_register(char *lexeme)
{
	size_t	i;

	if (lexeme[0] != REGISTER_CHAR)
		return (false);
	i = 1;
	while (lexeme[i] != '\0')
	{
		if (!ft_isdigit(lexeme[i]))
			return (false);
		i += 1;
	}
	return (true);
}

bool	is_directlabel(t_data *s_data, char *lexeme)
{
	if (lexeme[0] != DIRECT_CHAR)
		return (false);
	if (lexeme[1] != LABEL_CHAR)
		return (false);
	lexeme += 2;
	while (*lexeme != '\0')
	{
		if (ft_strchr(LABEL_CHARS, *lexeme) == NULL)
			lexical_error(s_data);
		lexeme += 1;
	}
	return (true);
}

bool	is_direct(t_data *s_data, char *lexeme)
{
	size_	i;

	i = 1;
	if (lexeme[0] != DIRECT_CHAR)
		return (false);
	if (lexeme[1] == LABEL_CHAR)
		return (false);
	if (lexeme[1] == '\0')
		return (false);
	if (lexeme[1] == '-')
		i += 1;
	while (lexeme[i] != '\0')
	{
		if (!ft_isdigit(lexeme[i]))
			lexical_error(s_data);
		i += 1;
	}
	return (true);
}

bool	is_indirect(t_data *s_data, char *lexeme)
{
	if (ft_isnumber(lexeme))
		return (true);
	if (lexeme[0] != LABEL_CHAR)
		return (false);
	if (contains_invalid_characters(s_data, lexeme))
		return (false);
	return (true);
}

bool	is_argument(t_type type)
{
	if (type == REGISTER || type == DIRECT_LABEL
		|| type == DIRECT || type == INDIRECT)
		return (true);
	return (false);
}
