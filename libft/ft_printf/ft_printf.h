/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:39:06 by hmaronen          #+#    #+#             */
/*   Updated: 2022/05/09 10:39:09 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

# define FORMATS "cspdiouxXf%%"

typedef struct s_flags
{
	va_list	args;
	int		width;
	int		space;
	int		zero;
	int		plus;
	int		minus;
	int		hash;
	int		precision;
	int		prec_len;
	int		arg_len;
	int		hh;
	int		h;
	int		l;
	int		ll;
	int		ret_len;
	int		is_neg;
	int		is_float;
}	t_flags;

typedef void	t_handler_func(t_flags *flag);

int			ft_printf(const char *format, ...);
void		check_flags(t_flags *flag, const char *str, char format);
void		check_length_modifiers(t_flags *flag, const char *str, char specif);

void		c_handler(t_flags *flag);
void		s_handler(t_flags *flag);
void		p_handler(t_flags *flag);
void		di_handler(t_flags *flag);
void		o_handler(t_flags *flag);
void		u_handler(t_flags *flag);
void		x_handler(t_flags *flag);
void		big_x_handler(t_flags *flag);
void		f_handler(t_flags *flag);
void		percent_handler(t_flags *flag);

void		put_ptr(uintptr_t addr);
int			put_padding(int width, char ch);

void		nb_padding(t_flags *flag, char *argument, char *prefix);
void		length_modifiers(t_flags *flag, long *ptr_nb);
void		unsigned_length_modifiers(t_flags *flag, unsigned long *ptr_nb);
long double	double_length_modifiers(t_flags *flag);

#endif