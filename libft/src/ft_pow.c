/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 13:23:53 by hmaronen          #+#    #+#             */
/*   Updated: 2022/07/04 13:23:54 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_pow(int base, int exponent)
{
	int	result;

	result = base;
	while (--exponent > 0)
		result *= base;
	return (result);
}
