/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 13:16:09 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/21 13:16:09 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	lookup(const char *string)
{
	size_t	i;

	i = 0;
	while (g_op_tab[i].instruction != NULL)
	{
		if (ft_strcmp(string, g_op_tab[i].instruction) == 0)
			return (g_op_tab[i].op_code);
		i += 1;
	}
	return (-1);
}

void	reel_to_end(t_data *s_data, char *string)
{
	while (*string != '\0')
	{
		s_data->s_error_log->column += 1;
		if (*string == COMMENT_CHAR)
			return ;
		if (!is_delim(*string))
			lexical_error(s_data);
		string += 1;
	}
}

int	contains_invalid_characters(t_data *s_data, char *lexeme)
{
	if (*lexeme == LABEL_CHAR)
	{
		lexeme += 1;
		s_data->s_error_log->column += 1;
	}
	if (*lexeme == '\0')
		lexical_error(s_data);
	while (*lexeme != ':' && *lexeme != '\0')
	{
		if (ft_strchr(LABEL_CHARS, *lexeme) == NULL)
			return (-1);
		lexeme += 1;
		s_data->s_error_log->column += 1;
	}
	return (0);
}

void	usage()
{
	ft_printf("Usage: asm [arg]\n\n");
	ft_printf("Arguments:\n");
	ft_printf("\tinput_file\tfile to process\n");
	exit(0);
}
