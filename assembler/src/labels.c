/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   labels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoponen <okoponen@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 13:29:27 by okoponen          #+#    #+#             */
/*   Updated: 2022/12/20 13:29:29 by okoponen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

int	is_label_call(char *current_arg)
{
	int	i;

	i = 0;
	while (current_arg[i])
	{
		if (current_arg[i] == ':')
			return (1);
		i++;
	}
	return (0);
}

/*
	Strcmp but we skip the first characters of the name if they are : or %.
	Compare two labels, if the names match we return 1, else we return 0.
*/
int	compare_labels(char *original_label, char *current_label)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (original_label[i] || current_label[j])
	{
		while (original_label[i] == ':' || original_label[i] == '%')
			i++;
		while (current_label[j] == ':' || current_label[j] == '%')
			j++;
		if (original_label[i] != current_label[j])
			return (0);
		if (original_label[i])
			i++;
		if (current_label[j])
			j++;
	}
	return (1);
}

/*
	function to loop through saved labels and compare their names to the label
	we are currently searching through. When we get a match we can substract
	the address our current postion from the address of that label to find
	the relative position of that label. 
*/
void	find_label_addr(t_stmnt **array, char *curr_label_name, int curr_arg, \
						int curr_struct)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (array[i]->label_name)
		{
			if (compare_labels(array[i]->label_name, curr_label_name))
			{
				array[curr_struct]->arg_values[curr_arg] = \
				array[i]->current_bytes - array[curr_struct]->current_bytes;
				return ;
			}
		}
		i++;
	}
	if (!array[i])
		syntax_error(UNDEFINED_LABEL_ERR, NULL, curr_label_name, NULL);
}
