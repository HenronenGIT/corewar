/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akilk <akilk@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/11/14 14:19:47 by akilk            ###   ########.fr       */
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
	// printf("name:%s\n", champion->name);
	// printf("comment:%s\n", champion->comment);
	// printf("size:%d\n", champion->code_size);
	// printf("bytecode:%02x\n", champion->code);

}

/* Add champions to list. Do we need this? */
// static void	add_champion(t_champion **list, t_champion *champion)
// {
// 	t_champion	*curr;

// 	if (*list)
// 	{
// 		curr = *list;
// 		while (curr->next)
// 			curr = curr->next;
// 		curr->next = champion;
// 	}
// 	else
// 		*list = champion;
// }

/*
** -n number
** sets the number of the next player.
** If non-existent, the player will have the next available number
** in the order of the parameters.
** The last player will have the first process in the order of execution.
*/

static bool	id_used(int id, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->champions_num)
	{
		if (id == data->champions[i]->id)
			return (true);
		i++;
	}
	return (false);
}

static void	parse_n(int *ac, char ***av, t_data *data, t_champion *champion)
{
	int		num;
	char	*name;

	if (*ac > 3 && !ft_strcmp(**av, "-n"))
	{
		num = ft_atoi(*(*av + 1));
		name = *(*av + 2);
		if (num < 1 || num > MAX_PLAYERS
			|| !is_cor_file(name)
			|| id_used(num, data))
		{
			printf("TEST USAGE\n");
			error(NULL, "Wrong usage of -n flag");
		}
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
	{
		printf("TEST USAGE\n");
		error(NULL, "It doesn't work that way");
	}
	data->champions_num++;
	data->champions[data->champions_num - 1] = champion;
}

static void	sort_ids(t_champion **unlisted, t_champion **result, t_data *data)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (unlisted[k] != NULL && i < data->champions_num)
	{
		if (result[i] == NULL)
		{
			result[i] = unlisted[k++];
			result[i]->id = i + 1;
		}
		i++;
	}
	i = -1;
	while (++i < data->champions_num)
		data->champions[i] = result[i];
}

static void	reset_ids(t_data *data)
{
	int			i;
	int			k;
	t_champion	*unlisted[MAX_PLAYERS];
	t_champion	*result[MAX_PLAYERS];

	i = 0;
	k = 0;
	ft_bzero(result, sizeof(result));
	ft_bzero(unlisted, sizeof(unlisted));
	while (i < data->champions_num)
	{
		if (data->champions[i]->id > data->champions_num)
		{
			printf("TEST USAGE\n");
			error(NULL, "champion's number is not correct");
		}
		else if (data->champions[i]->id == 0)
			unlisted[k++] = data->champions[i];
		else
			result[data->champions[i]->id - 1] =  data->champions[i];
		i++;
	}
	sort_ids(unlisted, result, data);
}

/* Parsing arguments */

void	parse(int ac, char **av, t_data *data)
{
	t_champion	*champion;
	// t_champion	*list;

	av++;
	// list = NULL;
	while (ac > 1)
	{
		if (!ft_strcmp(*av, "-dump"))
		{
			parse_dump(&ac, &av, data);
			data->dump_cycle = ft_atoi(*(av + 1));
			printf("dump: %d\n", data->dump_cycle);// used during game to dump after this cycle
		}
		else if (is_cor_file(*av) || !ft_strcmp(*av, "-n"))
		{
			champion = init_champion();
			parse_n(&ac, &av, data, champion);
		}
	}
	if (data->champions_num < 1 || data->champions_num > MAX_PLAYERS)
		error(NULL, "Champions amount should be between 1 and 4");
	reset_ids(data);

	//test id-s
	for (int i = 0; i < data->champions_num; i++)
	{
		printf("id %d name %s\n", data->champions[i]->id, data->champions[i]->name);
	}
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
	// test id
	// for (int i = 0; i < data->champions_num; i++)
	// {
	// 	printf("name: %s id: %d\n",data->champions[i]->name, data->champions[i]->id);
	// }
