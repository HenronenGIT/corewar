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

void error(int error_number)
{
	if (error_number == OPEN_ERR)
		ft_puterror("ERROR: Failed to open received file\n");
	if (error_number == ARG_ERR)
		ft_puterror("ERROR: Invalid amount of arguments\n");
	if (error_number == MALLOC_ERR)
		ft_puterror("ERROR: Malloc returned NULL!\n");
	if (error_number == NULL_ERR)
		ft_puterror("ERROR: NULL was passed to the function!\n");
	if (error_number == INVALID_LABEL)
		ft_puterror("ERROR: Label contained invalid characters!\n");
	if (error_number == NAME_LEN_ERR)
		ft_puterror("ERROR: Champion name too long (Max length 128)\n");
	if (error_number == COMMENT_LEN_ERR)
		ft_puterror("ERROR: Champion comment too long (Max length 2048)\n");
	exit(error_number);
}

char	*find_file_name(char *s)
{
	char	*file_name;
	int		i;
	int		len;
	int		j;

	i = 1;
	j = 0;
	file_name = NULL;
	s = ft_strrchr(s, '/');
	len = ft_strlen(s);
	printf("len: %d\n", len);
	file_name = ft_strnew(len + 3);
	file_name[len + 2] = '\0';
	while (s[i] && s[i] != '.')
	{
		file_name[j++] = s[i++];
	}
	file_name[i] = '\0';
	file_name = ft_strcat(file_name, ".cor");
	return (file_name);
}

int main(int argc, char *argv[])
{
//	t_data		s_data;
	t_header	s_header;
//	t_error_log	s_error_log;
	int			fd;

	printf("\n\n||%s||\n\n", find_file_name(argv[1]));
	fd = open(find_file_name(argv[1]), O_CREAT | O_WRONLY);
	printf("open returns: %d", fd);
	if (argc != 2)
		error(ARG_ERR);
//	init_structs(&s_data, &s_header, &s_error_log);
//	init_vectors(&s_data);
//	read_input(argv[1], &s_data);
//	syntax_analyzer(&s_data);
//	print_data(&s_data);
	add_magic(fd);
	hex_translator(s_header.prog_name, fd, PROG_NAME_LENGTH);
	hex_translator(s_header.comment, fd, COMMENT_LENGTH);
//	generator(s_data.vec_input);
	return (0);
}
