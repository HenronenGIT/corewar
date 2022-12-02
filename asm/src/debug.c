/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:47:33 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/21 13:47:34 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

#define PINK "\033[0;35m"
#define WHITE "\033[0;37m"
#define GREEN "\033[0;32m"

char *get_type(t_type type)
{
	static char *types_arr[] = {
		"NAME",
		"COMMENT",
		"LABEL",
		"INSTRUCTION",
		"SEPARATOR",
		"REGISTER",
		"DIRECT_LABEL",
		"DIRECT",
		"INDIRECT",
		"INVALID"};
	return (types_arr[type]);
}

void print_temp_name(t_vec *vec_input)
{
	size_t i;
	t_input **input_array;

	i = 0;
	input_array = (t_input **)vec_input->array;
	ft_printf("%s########### vec_input->array ###########%s\n", GREEN, WHITE);
	while (i < vec_input->space_taken)
	{
		ft_printf("%s[%d]%-8s", GREEN, i, WHITE);
		ft_printf("%slabel_name%s = %-8s\n", PINK, WHITE, input_array[i]->label_name);
		ft_printf("% 11sop_code%s = %-5d\n", PINK, WHITE, input_array[i]->op_code);

		ft_printf("% 11sargs[0]%s = %-8s", PINK, WHITE, input_array[i]->args[0]);
		ft_printf("%sargs[1]%s = %-8s", PINK, WHITE, input_array[i]->args[1]);
		ft_printf("% 11sargs[2]%s = %-8s\n", PINK, WHITE, input_array[i]->args[2]);

		ft_printf("% 11sarg_type[0]%s = %-4d", PINK, WHITE, input_array[i]->arg_type[0]);
		ft_printf("%sarg_type[1]%s = %-4d", PINK, WHITE, input_array[i]->arg_type[1]);
		ft_printf("%sarg_type[2]%s = %-4d\n", PINK, WHITE, input_array[i]->arg_type[2]);

		ft_printf("% 11sarg_size[0]%s = %-3d", PINK, WHITE, input_array[i]->arg_size[0]);
		ft_printf("%sarg_size[1]%s = %-3d", PINK, WHITE, input_array[i]->arg_size[1]);
		ft_printf("%sarg_size[2]%s = %-2d", PINK, WHITE, input_array[i]->arg_size[2]);
		ft_printf("\n");
		ft_printf("% 11scurrent_bytes%s = %-4d\n", PINK, WHITE, input_array[i]->current_bytes);
		// ft_printf("\n");

		ft_printf("% 11stotal_size%s = %-3d", PINK, WHITE, input_array[i]->total_size);
		ft_printf("\n");
		ft_printf("\n");
		// ft_printf("%sCONTENT%s = %s\n", PINK, WHITE, input_array[i]->label_name);
		i += 1;
	}
}

void print_tokens(t_vec *vec_tokens)
{
	size_t i;
	t_token **token_array;

	i = 0;
	token_array = (t_token **)vec_tokens->array;
	ft_printf("%s########### t_token ** vector ###########%s\n", GREEN, WHITE);

	while (i < vec_tokens->space_taken)
	{
		ft_printf("%s[%d]%s\t", GREEN, i, WHITE);
		ft_printf("%sTYPE%s = %-10s\t", PINK, WHITE, get_type(token_array[i]->type));
		ft_printf("%sCONTENT%s = %s\n", PINK, WHITE, token_array[i]->content);
		i += 1;
	}
	ft_printf("\n");
}

void print_header_data(t_header *s_header)
{
	ft_printf("%s########### t_header ###########%s\n", GREEN, WHITE);
	ft_printf("%s.name%s = \t|%s|\n", PINK, WHITE, s_header->prog_name);
	ft_printf("%s.comment%s = \t|%s|\n", PINK, WHITE, s_header->comment);
	// ft_printf("%sprog_size%s = \t|%s|\n", PINK, WHITE, s_header->prog_size);
	ft_printf("%smagic%s = \t|%d|\n", PINK, WHITE, s_header->magic);
	ft_printf("\n");
}

void print_data(t_data *s_data)
{
	print_header_data(s_data->s_header);
	print_tokens(s_data->vec_tokens);
	print_temp_name(s_data->vec_input);
}