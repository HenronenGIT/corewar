/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/11/08 15:11:34 by akilk            ###   ########.fr       */
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

/* parsing first 4 bytes to check magic header */

static int32_t	bytecode2int(uint8_t *bytecode, size_t size)
{
	int32_t	result;
	int		sign;
	int		i;

	result = 0;
	sign = 0;
	/* If first bit of first byte is 0x80*/
	if (bytecode[0] & 0x80)
		sign = 1;
	i = 0;
	while (size)
	{
		if (sign)
			result += ((bytecode[size - 1] ^ 0xFF) << (i++ * 8));
		else
			result += bytecode[size - 1] << (i++ * 8);
		size--;
	}
	if (sign)
		result = ~(result);
	printf("res:%d\n", result);
	return (result);
}

static int32_t parse_bytecode(int fd)
{
	ssize_t	ret;
	uint8_t	buffer[4];

	ret = read(fd, &buffer, 4);
	if (ret == -1)
		error(NULL, "Error reading file");
	if (ret < 4)
		error(NULL, "Invalid file");
	return (bytecode2int(buffer, ret));
}

/* Parsing champions name and comment */

static char	*parse_str(int fd, int len)
{
	char	*str;
	ssize_t	ret;

	str = ft_strnew(len);
	if(!str)
		error(NULL, "Allocation failed in parse_str()");
	ret = read(fd, str, len);
	if (ret <(ssize_t)len)
		error (&str, "Invalid file in parse_str()");
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
	if (parse_bytecode(fd) != COREWAR_EXEC_MAGIC)
		error(NULL, "Wrong magic number");
	champion->name = parse_str(fd, PROG_NAME_LENGTH);
	if (parse_bytecode(fd) != 0)
		error(NULL, "No NULL after name");
	//add code_size
	champion->comment = parse_str(fd, COMMENT_LENGTH);
	if (parse_bytecode(fd) != 0)
		error(NULL, "No NULL after comment");
	/* Testing outputs: */
	printf("s:%s\n", champion->name);
	printf("s:%s\n", champion->comment);
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
