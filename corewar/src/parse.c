/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/11/09 12:02:46 by akilk            ###   ########.fr       */
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

void	parse_champions(char *file, t_vm *vm)
{
	int	fd;
	t_champion	*champion;

	vm->champions_num++;
	champion = init_champion(vm->champions_num);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, "Wrong file");
	if (parse_bytes(fd) != COREWAR_EXEC_MAGIC)
		error(NULL, "Wrong magic number");
	champion->name = parse_data(fd, PROG_NAME_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after name");
	champion->code_size = parse_bytes(fd);
	printf("size:%d\n", champion->code_size);
	printf("max:%d\n", CHAMP_MAX_SIZE);
	if (champion->code_size < 0 || champion->code_size > CHAMP_MAX_SIZE)
		error(NULL, "Invalid champion's code size");
	champion->comment = parse_data(fd, COMMENT_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after comment");
	champion->code = parse_data(fd, champion->code_size);
	/* Testing decimals: */
	printf("name:%s\n", champion->name);
	printf("comment:%s\n", champion->comment);
	printf("bytecode:%02x\n", champion->code);
}

/* Parsing arguments */

void	parse(int argc, char **argv, t_vm *vm)
{
	t_champion	*list;

	list = NULL;
	argv++;
	while (argc > 1)
	{
		/* if (!ft_strcmp(*argv, "-dump")
			parse_dump();
		*/
		/* else if (!ft_strcmp(*argv, "-n")
			parse_n_flag();
		*/
		if (is_cor_file(*argv))
		{
			parse_champions(*argv, vm);
		}
		// printf("s:%s\n", *argv);
		argv++;
		argc--;
	}
	if (vm->champions_num < 1 || vm->champions_num > MAX_PLAYERS)
		error(NULL, "Champions amount should be between 1 and 4");
}
