
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmaronen <hmaronen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:01:25 by hmaronen          #+#    #+#             */
/*   Updated: 2022/11/07 14:01:26 by hmaronen         ###   ########.fr       */
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
	{
		file_name[j++] = temp[i++];
	}
	file_name[i] = '\0';
	file_name = ft_strcat(file_name, ".cor");
	return (file_name);
}

void	write_champ_code(t_data *data, int fd)
{
	int		temp;
	int		i;
	char	*exec_size;

	temp = 0;
	i = 0;
	exec_size = NULL;
	write(fd, &temp, 2);
	write(fd, &temp, 2);
	write(fd, &temp, 2);
	exec_size = ft_itoa_base(data->champ_size, 16);
	write(fd, &temp, 1);
	hex_translator(exec_size, fd, 1);
	free (exec_size);
}

int	main(int argc, char *argv[])
{
	t_data		s_data;
	t_header 	s_header;
	t_error_log	s_error_log;
	int			fd;
	uint32_t	magic;

	magic = 0x00ea83f3;
//	printf("\n\n||%s||\n\n", find_file_name(argv[1]));
 	if (argc != 2)
		error(ARG_ERR);
	fd = open(find_file_name(argv[1]), O_RDWR | O_CREAT | O_TRUNC, 0600);
	init_structs(&s_data, &s_header, &s_error_log);
	init_vectors(&s_data);
	read_input(argv[1], &s_data);
	syntax_analyzer(&s_data);
	calculate_statement_sizes(&s_data);
	// print_data(&s_data); //! temp
//	printf("magic 0x%x\n", magic);
	magic = int_to_bigendian(magic, 4);
	// magic = int_to_bigendian(COREWAR_EXEC_MAGIC, 4);
//	printf("magic 0x%x\n", magic);
	write(fd, &magic, 4);
	hex_translator(s_data.s_header->prog_name, fd, PROG_NAME_LENGTH);
	write_champ_code(&s_data, fd);
	hex_translator(s_data.s_header->comment, fd, COMMENT_LENGTH);
	generator(s_data.vec_input, fd);
	return (0);
}
