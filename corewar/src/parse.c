/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 15:19:05 by akilk             #+#    #+#             */
/*   Updated: 2022/12/05 13:27:20 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"

static int32_t parse_bytes(int fd)
{
	ssize_t	ret;
	uint8_t	byte_value[4];

	ret = read(fd, &byte_value, 4);
	if (ret == -1)
		error(NULL, "Error reading file", 0);
	if (ret < 4)
		error(NULL, "Invalid file", 0);
	return (bytes2int(byte_value, ret));
}

/* Parsing champions name and comment */

static char	*parse_data(int fd, int32_t size)
{
	char	*str;
	ssize_t	ret;

	str = ft_strnew(size);
	if(!str)
		error(NULL, "Allocation failed in parse_data()", 0);
	ret = read(fd, str, size);
	if (ret < (ssize_t)size)
		error (&str, "Invalid file in parse_data()", 0);
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

void	parse_champions(char *file, t_champion *champion)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		error(NULL, "Wrong file", 1);
	if (parse_bytes(fd) != COREWAR_EXEC_MAGIC)
		error(NULL, "Wrong magic number", 1);
	champion->name = parse_data(fd, PROG_NAME_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after name", 1);
	champion->code_size = parse_bytes(fd);
	if (champion->code_size < 0 || champion->code_size > CHAMP_MAX_SIZE)
		error(NULL, "Invalid champion's code size", 1);
	champion->comment = parse_data(fd, COMMENT_LENGTH);
	if (parse_bytes(fd) != 0)
		error(NULL, "No NULL after comment", 1);
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
			parse_dump(&ac, &av, data);
		else if (is_cor_file(*av) || !ft_strcmp(*av, "-n"))
		{
			champion = init_champion();
			parse_n(&ac, &av, data, champion);
		}
		else if (!ft_strcmp(*av, "-v"))
			parse_verbosity(&ac, &av, data);
		else
			error(NULL, "Error in parse()", 1);
	}
	if (data->champions_num < 1 || data->champions_num > MAX_PLAYERS)
		error(NULL, "Champions amount should be between 1 and 4", 0);
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
