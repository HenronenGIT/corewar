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

char	*get_type(t_type type)
{
	static char *types_arr[9] ={
	"NAME",
	"COMMENT",
	"LABEL",
	"STATEMENT",
	"SEPARATOR",
	"REGISTER",
	"DIRECT_LABEL",
	"DIRECT",
	"INVALID"
	};

	return (types_arr[type]);
}

void	print_tokens(t_vec *vec_tokens)
{
	size_t	i;
	t_token **token_array;

	i = 0;
	token_array = (t_token **)vec_tokens->array;
	ft_printf("%s------ t_token ** vector ------%s\n", GREEN, WHITE);

	while (i < vec_tokens->space_taken)
	{
		ft_printf("%s[%d]%s\t", GREEN, i, WHITE);
		ft_printf("%sTYPE%s = %-10s\t", PINK, WHITE, get_type(token_array[i]->type));
		ft_printf("%sCONTENT%s = %s\n", PINK, WHITE ,token_array[i]->content);
		i += 1;
	}
}

void	print_header_data(t_header *s_header)
{
	ft_printf("%s------ t_header ------%s\n", GREEN, WHITE);
	ft_printf("%s.name%s = \t|%s|\n", PINK, WHITE, s_header->prog_name);
	ft_printf("%s.comment%s = \t|%s|\n", PINK, WHITE, s_header->comment);
	// ft_printf("%sprog_size%s = \t|%s|\n", PINK, WHITE, s_header->prog_size);
	// ft_printf("%smagic%s = \t|%d|\n", PINK, WHITE, s_header->magic);
}

void	print_data(t_data *s_data)
{
	print_header_data(s_data->s_header);
	print_tokens(s_data->vec_tokens);
}