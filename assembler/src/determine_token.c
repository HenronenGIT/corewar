/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determine_token.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:06:49 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/21 17:06:50 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

bool	is_separator(char c)
{
	if (c == SEPARATOR_CHAR)
		return (true);
	return (false);
}

/*
Validates if lexeme literal matches specifications of LABEL.
*/
bool	is_label(t_data *s_data, char *lexeme)
{
	char	*found_colon;

	if (lexeme[0] == LABEL_CHAR)
		return (false);
	found_colon = NULL;
	found_colon = ft_strchr(lexeme, LABEL_CHAR);
	if (found_colon == NULL)
		return (false);
	if (*(found_colon + 1) != '\0')
		return (false);
	if (contains_invalid_characters(s_data, lexeme))
		lexical_error(s_data);
	return (true);
}

bool	is_delim(char c)
{
	if (c == ' ' || c == '\t' || c == SEPARATOR_CHAR || c == '\0')
		return (true);
	return (false);
}

bool	is_statement(char *lexeme)
{
	if (!ft_strcmp(lexeme, "live") || !ft_strcmp(lexeme, "ld")
		|| !ft_strcmp(lexeme, "st") || !ft_strcmp(lexeme, "add")
		|| !ft_strcmp(lexeme, "sub") || !ft_strcmp(lexeme, "and")
		|| !ft_strcmp(lexeme, "or") || !ft_strcmp(lexeme, "xor")
		|| !ft_strcmp(lexeme, "zjmp") || !ft_strcmp(lexeme, "ldi")
		|| !ft_strcmp(lexeme, "sti") || !ft_strcmp(lexeme, "fork")
		|| !ft_strcmp(lexeme, "lld") || !ft_strcmp(lexeme, "lldi")
		|| !ft_strcmp(lexeme, "lfork") || !ft_strcmp(lexeme, "aff"))
		return (1);
	return (0);
}
