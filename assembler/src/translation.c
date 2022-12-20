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

/*
	Created file must be named the same as the input file with the exception
	of it having a .cor suffix instead of .s. This function will remove
	the .s suffix and replace it with .cor.
*/
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

/*
	take the size of the champion, convert it to big endian
	and write it in the file.
*/
void	write_champ_code(t_data *data, int fd)
{
	data->champ_size = int_to_bigendian(data->champ_size, 4);
	write(fd, &data->champ_size, 4);
}

/*
	write 4 null bytes in the file when this function is called
*/
void	put_null(int fd)
{
	int	null;

	null = 0;
	write(fd, &null, 4);
}


/*
	translate magic header, program name, and comment to hexadecimal and
	print them in the file descriptor. Call generator which will also
	print the generated champion exec code to the given file descriptor.
*/
void	translation(t_data *s_data, char *file_name)
{
	int			fd;
	uint32_t	magic;
	char		*new_file_name;

	new_file_name = find_file_name(file_name);
	file_name[ft_strlen(file_name) - 2] = '\0';
	ft_printf("Writing output program to %s.cor\n", file_name);
	magic = COREWAR_EXEC_MAGIC;
	fd = open(new_file_name, O_RDWR | O_CREAT | O_TRUNC, 0600);
	magic = int_to_bigendian(COREWAR_EXEC_MAGIC, 4);
	write(fd, &magic, 4);
	hex_translator(s_data->s_header->prog_name, fd, PROG_NAME_LENGTH);
	put_null(fd);
	write_champ_code(s_data, fd);
	hex_translator(s_data->s_header->comment, fd, COMMENT_LENGTH);
	put_null(fd);
	generator(s_data->vec_input, fd);
	close(fd);
}
