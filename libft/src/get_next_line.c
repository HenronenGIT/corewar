/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 10:12:40 by hmaronen          #+#    #+#             */
/*   Updated: 2021/12/15 10:12:41 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/get_next_line.h"
#include "../includes/libft.h"

static int	check_newline(char *str)
{
	if (!(str))
		return (0);
	if (ft_strchr(str, '\n') != L_NOT_FOUND)
		return (1);
	else
		return (0);
}

static void	set_line(int fd, char **fd_arr, char **line)
{
	char	*remain;
	int		len;
	int		line_len;

	if (check_newline(fd_arr[fd]) == L_NOT_FOUND)
	{
		*line = ft_strdup(fd_arr[fd]);
		if (!(line))
			return ;
		ft_strdel(&fd_arr[fd]);
	}
	else
	{
		len = ft_strlen(fd_arr[fd]);
		line_len = find_eofl(fd_arr[fd]);
		*line = ft_strndup(fd_arr[fd], find_eofl(fd_arr[fd]));
		if (**line == '\n')
			ft_strclr(*line);
		remain = ft_strndup(ft_strchr(fd_arr[fd], '\n') + 1, (len - line_len));
		free(fd_arr[fd]);
		fd_arr[fd] = remain;
	}
}

static int	read_until_newline(int fd, char **fd_arr)
{
	char	buf[BUFF_SIZE + 1];
	int		bytes_read;

	while (check_newline(fd_arr[fd]) == L_NOT_FOUND)
	{
		bytes_read = read(fd, buf, BUFF_SIZE);
		if (bytes_read == -1)
			return (-1);
		buf[bytes_read] = '\0';
		if (bytes_read == 0)
		{
			if (!(fd_arr[fd]) || *fd_arr[fd] == '\0')
				return (L_NOT_FOUND);
			else
				return (1);
		}
		if (!(fd_arr[fd]))
			fd_arr[fd] = ft_strdup(buf);
		else
			ft_realloc(&fd_arr[fd], buf);
	}
	return (L_FOUND);
}

int	get_next_line(const int fd, char **line)
{
	static char	*fd_arr[MAX_FD];
	int			read_return;

	if (fd < 0 || line == NULL || fd >= MAX_FD)
		return (-1);
	read_return = read_until_newline(fd, fd_arr);
	if (read_return == FD_DONT_EXIST)
		return (-1);
	if (read_return == L_FOUND)
	{
		set_line(fd, fd_arr, line);
		return (L_FOUND);
	}
	else
	{
		ft_strdel(&fd_arr[fd]);
		return (0);
	}
}
