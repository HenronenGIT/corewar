/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_n.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:31:42 by wdonnell          #+#    #+#             */
/*   Updated: 2022/12/15 14:42:58 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

static char	*parse_info(int fd, int32_t size)
{
	char	*str;
	ssize_t	ret;

	str = ft_strnew(size);
	if (!str)
		error(NULL, "Allocation failed in parse_info()", 0);
	ret = read(fd, str, size);
	if (ret < (ssize_t)size)
		error (&str, "Invalid file in parse_info()", 0);
	return (str);
}

static int32_t	parse_bytes(int fd)
{
	ssize_t	ret;
	uint8_t	byte_value[4];

	ret = read(fd, &byte_value, 4);
	if (ret == -1)
		error(NULL, "Error reading file", 0);
	if (ret < 4)
		error(NULL, "Invalid file", 0);
	return (bytes2int(byte_value, 0, ret));
}

static void	parse_champions(char *file, t_champion *champion)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, "Wrong file", 1);
	if (parse_bytes(fd) != COREWAR_EXEC_MAGIC)
		error(NULL, "Wrong magic number", 1);
	champion->name = parse_info(fd, PROG_NAME_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after name", 1);
	champion->code_size = parse_bytes(fd);
	if (champion->code_size < 0 || champion->code_size > CHAMP_MAX_SIZE)
		error(NULL, "Invalid champion's code size", 1);
	champion->comment = parse_info(fd, COMMENT_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after comment", 1);
	champion->code = parse_info(fd, champion->code_size);
	if (close(fd) == -1)
		exit (1);
}

void	parse_n(int *ac, char ***av, t_data *data, t_champion *champion)
{
	int		num;
	char	*name;

	if (*ac > 3 && !ft_strcmp(**av, "-n"))
	{
		num = ft_atoi(*(*av + 1));
		name = *(*av + 2);
		if (num < 1 || num > MAX_PLAYERS || !is_cor_file(name) \
				|| id_used(num, data))
			error(NULL, "Error in parse_n()", 1);
		champion->id = num;
		parse_champions(name, champion);
		(*ac) -= 3;
		(*av) += 3;
	}
	else if (is_cor_file(**av))
	{
		parse_champions(**av, champion);
		(*ac)--;
		(*av)++;
	}
	else
		error(NULL, "Error in parse_n()", 1);
	data->champions_num++;
	data->champions[data->champions_num - 1] = champion;
}
