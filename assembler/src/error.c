/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:22:46 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/09 16:22:46 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void error(int error_number)
{
	if (error_number == OPEN_ERR)
		ft_puterror("ERROR: Failed to open received file\n");
	if (error_number == ARG_ERR)
		ft_puterror("ERROR: Invalid amount of arguments\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("ERROR: Malloc returned NULL!\n");
	if (error_number == NULL_ERR)
		ft_puterror("ERROR: NULL was passed to the function!\n");
	if (error_number == INVALID_LABEL)
		ft_puterror("ERROR: Label contained invalid characters!\n");
	if (error_number == NAME_LEN_ERR)
		ft_puterror("ERROR: Champion name too long (Max length 128)\n");
	if (error_number == COMMENT_LEN_ERR)
		ft_puterror("ERROR: Champion comment too long (Max length 2048)\n");
	if (error_number == NAME_COUNT_ERR)
		ft_puterror("ERROR: File contained multiple .name!\n");
	if (error_number == COMMENT_COUNT_ERR)
		ft_puterror("ERROR: File contained multiple .comment\n");
	if (error_number == MISSING_COMMA_ERR)
		ft_puterror("ERROR: Missing comma between arguments!\n");
	if (error_number == INVALID_FILE_NAME_ERR)
		ft_puterror("ERROR: Invalid filename\n");
	if (error_number == NO_NL_ERR)
		ft_puterror("ERROR: File was missing a newline character!\n");
	exit(error_number);
}

/*
Output error messages, and specify in which line that error happened.
*/
void	lexical_error(t_data *s_data)
{
	size_t	line_count;
	size_t	column_count;

	line_count = s_data->s_error_log->line;
	column_count = s_data->s_error_log->column;
	ft_printf("Lexical error at [%d:%d]\n", line_count, column_count);
	error(LEXICAL_ERROR);
}

/*
Is called form syntax_analyzer
*/
void	syntax_error(int error_number, int op_code)
{
	if (error_number == ARG_COUNT_ERR)
		ft_printf("Invalid amount of arguments for instruciton [%s]\n", g_table[op_code - 1].instruction);
	if (error_number == INVALID_ARG_ERR)
		ft_printf("Invalid argument type for instruction [%s]\n", g_table[op_code - 1].instruction);
	exit(SYNTAX_ERROR);

}
