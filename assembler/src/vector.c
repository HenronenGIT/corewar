/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.  c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:33:00 by hmaronen          #+#    #+#             */
/*   Updated: 2022/09/07 15:33:01 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

static void	vec_copy(t_vec *src, t_vec *dst)
{
	size_t	i;

	if (!src || !dst)
		error(NULL_ERR);
	i = 0;
	while (i < src->length)
	{
		dst->array[i] = src->array[i];
		i++;
	}
	dst->space_taken = i;
	dst->space_left = dst->length - dst->space_taken;
}

static void	vec_free(t_vec *vector)
{
	if (vector)
	{
		if (vector->array)
			free(vector->array);
	}
}

static void	vec_resize(t_vec *src)
{
	t_vec	dst;

	if (!src)
		error(NULL_ERR);
	vec_new_arr(&dst, (src->length * 2));
	vec_copy(src, &dst);
	vec_free(src);
	*src = dst;
}

void	vec_insert(t_vec *dst_vec, void *element)
{
	if (dst_vec->space_left == 0)
		vec_resize(dst_vec);
	dst_vec->array[dst_vec->space_taken] = element;
	dst_vec->space_taken++;
	dst_vec->space_left--;
}

void	vec_new_arr(t_vec *dst, size_t len)
{
	size_t	i;

	i = 0;
	if (!dst || len == 0)
		error(NULL_ERR);
	dst->length = len;
	dst->space_taken = 0;
	dst->space_left = len;
	dst->array = (void **)malloc(sizeof(void *) * (len + 1));
	if (!dst->array)
		error(MALLOC_ERR);
	while (i <= len)
		dst->array[i++] = NULL;
}
