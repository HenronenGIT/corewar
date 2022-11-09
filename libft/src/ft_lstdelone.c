/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:09:49 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/26 15:47:29 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*
*	Takes as a parameter a link’s pointer address and frees the
*	memory of the link’s content using the function del given as
*	a parameter, then frees the link’s memory using free(3). The
*	memory of next must not be freed under any circumstance.
*	Finally, the pointer to the link that was just freed must be
*	set to NULL (quite similar to the function ft_memdel in the
*	mandatory part). */

void	ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (!*alst || !del)
		return ;
	del((*alst)->content, (*alst)->content_size);
	free(*alst);
	*alst = NULL;
}
