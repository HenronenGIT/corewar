/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 13:12:49 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/09 13:12:50 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000
# define MAX_FD 4096
# define FD_DONT_EXIST -1
# define L_FOUND 1
# define L_NOT_FOUND 0
# define NOT_FOUND 0

# include "libft.h"

int	get_next_line(const int fd, char **line);

#endif
