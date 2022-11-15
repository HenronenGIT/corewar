/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:39:07 by hmaronen          #+#    #+#             */
/*   Updated: 2021/11/26 16:43:19 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/*	Takes as a parameter the adress of a pointer to a link and
*	frees the memory of this link and every successors of that link
*	using the functions del and free(3). Finally the pointer to
*	the link that was just freed must be set to NULL (quite similar
*	to the function ft_memdel from the mandatory part).
*/

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list	*next;
	t_list	*current;

	current = (*alst);
	while (current)
	{
		next = current->next;
		ft_lstdelone(&current, del);
		free(current);
		current = next;
	}
	*alst = NULL;
}
