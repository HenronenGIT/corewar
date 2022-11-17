/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_types.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wdonnell <wdonnell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 11:55:05 by wdonnell          #+#    #+#             */
/*   Updated: 2022/11/17 12:58:05 by wdonnell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/corewar.h"
#include "../includes/op_table.h"

static void get_arg1(int8_t byte, t_types *types)
{
	if ((byte & ARG1_MASK )== 0x40)
	{
		types->t_arg1 = T_REG;
		types->size_arg1 = 1;
	}
		
	else if ((byte & ARG1_MASK) == 0x80)
	{
		types->t_arg1 = T_DIR;
		types->size_arg1 = types->size_t_dir;

	}
	else if ((byte & ARG1_MASK) == 0xC0)
	{
		types->t_arg1 = T_IND;
		types->size_arg1 = 2;
	}
}

static void get_arg2(int8_t byte, t_types *types)
{
	if ((byte & ARG2_MASK )== 0x10)
	{
		types->t_arg2 = T_REG;
		types->size_arg2 = 1;
	}
	else if ((byte & ARG2_MASK) == 0x20)
	{
		types->t_arg2 = T_DIR;
		types->size_arg2 = types->size_t_dir;
	}
	else if ((byte & ARG2_MASK) == 0x30)
	{
		types->t_arg2 = T_IND;
		types->size_arg2 = 2;
	}
}

static void get_arg3(int8_t byte, t_types *types)
{
	if ((byte & ARG3_MASK) == 0x4)
	{
		types->t_arg3 = T_REG;
		types->size_arg3 = 1;
	}
	else if ((byte & ARG3_MASK )== 0x8)
	{
		types->t_arg3 = T_DIR;
		types->size_arg3 = types->size_t_dir;
	}
	else if ((byte & ARG3_MASK )== 0xC)
	{
		types->t_arg3 = T_IND;
		types->size_arg3 = 2;
	}
}

void get_types(int8_t byte, t_types *types)
{
	get_arg1(byte, types);
	get_arg2(byte, types);
	get_arg3(byte, types);
}