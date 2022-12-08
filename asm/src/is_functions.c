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

static int contains_invalid_characters(t_data *s_data, char *lexeme)
{
	while (*lexeme != ':')
	{
		if (ft_strchr(LABEL_CHARS, *lexeme) == NULL)
			return (-1);
		lexeme += 1;
	}
	return (0);
}

/*
Validates if lexeme literal matches specifications of LABEL.
*/
bool is_label(t_data *s_data, char *lexeme)
{
	char *found_colon;

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

bool is_delimiter(char c)
{
	if (c == ' ' || c == '\t' || c == SEPARATOR_CHAR || c == '\0')
		return (true);
	return (false);
}

bool is_statement(char *lexeme)
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

bool is_register(char *lexeme)
{
	size_t i;

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

bool is_separator(char c)
{
	if (c == SEPARATOR_CHAR)
		return (true);
	return (false);
}

bool is_directlabel(t_data *s_data, char *lexeme)
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

bool is_direct(t_data *s_data, char *lexeme)
{
	size_t i;

	i = 1;
	if (lexeme[0] != DIRECT_CHAR)
		return (false);
	if (lexeme[1] == LABEL_CHAR)
		return (false);
	// if (lexeme[1] == '-')
	// i += 1;
	while (lexeme[i] != '\0')
	{
		if (!ft_isdigit(lexeme[i]))
			lexical_error(s_data);
		i += 1;
	}
	return (true);
}

bool is_indirect(t_data *s_data, char *lexeme)
{
	if (ft_isnumber(lexeme))
		return true;
	if (lexeme[0] != LABEL_CHAR)
		return (false);
	if (contains_invalid_characters(s_data, lexeme))
		return (false);
	return (true);
}
