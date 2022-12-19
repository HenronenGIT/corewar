/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:39:31 by okoponen          #+#    #+#             */
/*   Updated: 2022/12/14 21:39:32 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char	*find_file_name(char *s)
{
	char	*file_name;
	int		i;
	int		len;
	int		j;
	char	*temp;

	i = 1;
	j = 0;
	file_name = NULL;
	temp = ft_strrchr(s, '/');
	if (!temp)
	{
		temp = s;
		i = 0;
	}
	len = ft_strlen(temp) - 2;
	file_name = ft_strnew(len + 3);
	file_name[len + 2] = '\0';
	while (len - i)
		file_name[j++] = temp[i++];
	file_name[i] = '\0';
	file_name = ft_strcat(file_name, ".cor");
	return (file_name);
}

void	write_champ_code(t_data *data, int fd)
{
	data->champ_size = int_to_bigendian(data->champ_size, 4);
	write(fd, &data->champ_size, 4);
}

void	put_null(int fd)
{
	int	null;

	null = 0;
	write(fd, &null, 4);
}

void	translation(t_data *s_data, char *file_name)
{
	int			fd;
	uint32_t	magic;

	magic = 0x00ea83f3;
	fd = open(find_file_name(file_name), O_RDWR | O_CREAT | O_TRUNC, 0600);
	magic = int_to_bigendian(magic, 4);
	write(fd, &magic, 4);
	hex_translator(s_data->s_header->prog_name, fd, PROG_NAME_LENGTH);
	put_null(fd);
	write_champ_code(s_data, fd);
	hex_translator(s_data->s_header->comment, fd, COMMENT_LENGTH);
	put_null(fd);
	generator(s_data->vec_input, fd);
	close(fd);
}