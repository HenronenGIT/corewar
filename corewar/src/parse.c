/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/11/15 11:00:22 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

/*
** Check if champion's filename is ending with extension .cor
*/

static int	is_cor_file(char *file)
{
	if ( ft_strlen(file) >= 4)
		return (!ft_strcmp(ft_strchr(file, '\0') - ft_strlen(".cor"), ".cor"));
	else
		return (0);
}

/*
** Converting bytes to signed integer using bitwise operators.
** If signed bit is 1, apply masking.
*/

/*
  Bitwise    Logical
+----------+---------+
|  a & b   |  a && b |
+----------+---------+
| a ^ b    |  a != b |
+----------+---------+
|    ~a    |   !a    |
+----------+---------+
*/

static int32_t	bytes2int(uint8_t *byte_value, size_t size)
{
	int		signbit;
	int		n;
	int32_t	decimal;

	decimal = 0;
	signbit = 0;
	if (byte_value[0] & 0x80)
		signbit = 1;
	n = 0;
	while (size)
	{
		if (signbit)
			decimal += ((byte_value[size - 1] ^ 0xFF) << (n * 8));
		else
			decimal += byte_value[size - 1] << (n * 8);
		n++;
		size--;
	}
	if (signbit)
		decimal = ~(decimal);
	return (decimal);
}

static int32_t parse_bytes(int fd)
{
	ssize_t	ret;
	uint8_t	byte_value[4];

	ret = read(fd, &byte_value, 4);
	if (ret == -1)
		error(NULL, "Error reading file");
	if (ret < 4)
		error(NULL, "Invalid file");
	return (bytes2int(byte_value, ret));
}

/* Parsing champions name and comment */

static char	*parse_data(int fd, int32_t size)
{
	char	*str;
	ssize_t	ret;

	str = ft_strnew(size);
	if(!str)
		error(NULL, "Allocation failed in parse_data()");
	ret = read(fd, str, size);
	if (ret < (ssize_t)size)
		error (&str, "Invalid file in parse_data()");
	return (str);
}

/*
	Parsing champions data:
	First 4 bytes - magic header,
	next 128 bytes - champion's name,
	next 4 bytes - null,
	next 4 bytes - champion's code size,
	next 2048 bytes - champion's comment,
	next 4 bytes - null,
	last part - champion's code.
 */

static void	parse_champions(char *file, t_champion *champion)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, "Wrong file");
	if (parse_bytes(fd) != COREWAR_EXEC_MAGIC)
		error(NULL, "Wrong magic number");
	champion->name = parse_data(fd, PROG_NAME_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after name");
	champion->code_size = parse_bytes(fd);
	if (champion->code_size < 0 || champion->code_size > CHAMP_MAX_SIZE)
		error(NULL, "Invalid champion's code size");
	champion->comment = parse_data(fd, COMMENT_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after comment");
	champion->code = parse_data(fd, champion->code_size);
	if (close(fd) == -1)
		exit (1);
	/* Testing output: */
	printf("name:%s\n", champion->name);
	printf("comment:%s\n", champion->comment);
	printf("size:%d\n", champion->code_size);
	// printf("bytecode:%02x\n", champion->code);

}

static void	add_champion(t_champion **list, t_champion *champion)
{
	t_champion	*curr;

	if (*list)
	{
		curr = *list;
		while (curr->next)
			curr = curr->next;
		curr->next = champion;
	}
	else
		*list = champion;
}

/* Parsing arguments */

void	parse(int ac, char **av, t_data *data)
{
	t_champion	*champion;
	t_champion	*list;

	av++;
	list = NULL;
	while (ac > 1)
	{
		// if (!ft_strcmp(*av, "-dump")
		// {
		// 	parse_dump(data);
		// 	av++;
		// 	ac--;
		// }
		/* else if (!ft_strcmp(*av, "-n")
			parse_n_flag();
		*/
		if (is_cor_file(*av))
		{
			data->champions_num++;
			champion = init_champion(data->champions_num);
			parse_champions(*av, champion);
			data->champions[data->champions_num - 1] = champion;
		}
		av++;
		ac--;
	}
	if (data->champions_num < 1 || data->champions_num > MAX_PLAYERS)
		error(NULL, "Champions amount should be between 1 and 4");
}
	// while (list)
	// {
	// 	printf("listed names: %s\n", list->name);
	// 	list = list->next;
	// }

	// /* test list */
	// for (size_t i = 0; i < data->champions_num; i++)
	// {
	// 	printf("champ[%zu]:%s\n",i, data->champions[i]->name);
	// }
