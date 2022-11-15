/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:38:21 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/03 13:19:36 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Allocates (with malloc(3)) and returns a “fresh” link. The
*	variables content and content_size of the new link are initialized
*	by copy of the parameters of the function. If the parameter content is nul,
*	the variable content is initialized to
*	NULL and the variable content_size is initialized to 0 even
*	if the parameter content_size isn’t. The variable next is
*	initialized to NULL. If the allocation fails, the function returns
*	NULL.
*/

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	if (content == NULL)
	{
		tmp->content = NULL;
		tmp->content_size = 0;
	}
	else
	{
		tmp->content_size = content_size;
		tmp->content = ft_memalloc(content_size);
		ft_memcpy(tmp->content, content, content_size);
	}
	tmp->next = NULL;
	return (tmp);
}
