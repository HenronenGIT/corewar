
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_analyzer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 10:39:20 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/22 10:39:21 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	syntax_analysis(t_data *s_data, int expected)
{
	t_token **token_array;
	size_t	i;

	i = 0;

	token_array = (t_token **)s_data->vec_tokens->array;
	while (i < s_data->vec_tokens->space_taken)
	{
		
		i += 1;
	}
}