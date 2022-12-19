/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.Hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 21:39:31 by hmaronen          #+#    #+#             */
/*   Updated: 2022/12/14 21:39:32 by hmaronen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

char *find_file_name(char *s)
{
	char *file_name;
	int i;
	int len;
	int j;
	char *temp;

	i = 1;
	j = 0;
	file_name = NULL;
	temp = ft_strdup(s);
	temp = ft_strrchr(s, '/');
	if (!temp)
	{
		temp = s;
		i = 0;
	}
	len = ft_strlen(temp);
	// printf("len: %d\n", len);
	file_name = ft_strnew(len + 3);
	file_name[len + 2] = '\0';
	while (temp[i] && temp[i] != '.')
		file_name[j++] = temp[i++];
	file_name[i] = '\0';
	file_name = ft_strcat(file_name, ".cor");
	return (file_name);
}

void	write_champ_code(t_data *data, int fd)
{
	printf("data->champ_size in b10: %d\n", data->champ_size);
	data->champ_size = int_to_bigendian(data->champ_size, 4);
	write(fd, &data->champ_size, 4);
	// int		temp;

	// temp = 0;
	// write(fd, &temp, 2);
	// write(fd, &temp, 1);
	// write(fd, &data->champ_size, 1);
}

void	put_null(int fd)
{
	int null;

	null = 0;
	write(fd, &null, 4);
}

void	translation(t_data *s_data, char *file_name)
{
	int	fd;
	uint32_t magic;

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
