/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:23:07 by gonische          #+#    #+#             */
/*   Updated: 2024/11/14 22:54:45 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_node_list	*ft_get_new_node(char *data)
{
	t_node_list	*result;

	result = (t_node_list *)ft_calloc(1, sizeof(t_node_list));
	if (!result)
		return (NULL);
	if (data)
		result->data = data;
	else
	{
		result->data = (char *)ft_calloc(LINE_DATA_SIZE + 1, sizeof(char));
		if (!result->data)
		{
			free(result);
			return (NULL);
		}
	}
	result->next = NULL;
	return (result);
}
