/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:05:07 by gonische          #+#    #+#             */
/*   Updated: 2024/11/14 22:54:31 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>			// used for printf
#include <stdbool.h>
#include <unistd.h>

int	ft_read(int fd, t_data *data)
{
	data->bytes_read = read(fd, &data->buffer[0], BUFFER_SIZE);
	data->i = 0;
	data->last_fd = fd;
	if (data->bytes_read >= 0)
		data->buffer[data->bytes_read] = '\0';
	return (data->bytes_read);
}

void	ft_free(t_node_list *line)
{
	t_node_list	*next;

	while (line)
	{
		next = line->next;
		free(line->data);
		free(line);
		line = next;
	}
}

void	ft_parse_line(int fd, t_data *data, const t_node_list *line)
{
	int			i;
	t_node_list	*tail;

	i = 0;
	tail = (t_node_list *)line;
	if (!data->buffer[data->i] || fd != data->last_fd)
		data->bytes_read = ft_read(fd, data);
	while (true)
	{
		if ((data->bytes_read <= 0 && data->buffer[data->i] == '\0')
			|| (i > 0 && tail->data[i - 1] == '\n'))
			break ;
		if (data->i >= BUFFER_SIZE || data->buffer[data->i] == '\0')
			data->bytes_read = ft_read(fd, data);
		if (tail->data[i] == '\0' && i > 0)
		{
			tail->next = ft_get_new_node(NULL);
			tail = tail->next;
			i = 0;
		}
		if (data->buffer[data->i])
			tail->data[i++] = data->buffer[data->i++];
	}
}

char	*ft_get_result(t_node_list *line)
{
	char		*result;
	size_t		line_len;
	size_t		i;
	t_node_list	*tail;

	tail = line;
	line_len = 1;
	while (tail)
	{
		line_len += ft_strlen(tail->data);
		tail = tail->next;
	}
	tail = line;
	result = ft_calloc(line_len, sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	while (tail)
	{
		i += ft_strlcpy(&result[i], tail->data, line_len - i);
		tail = tail->next;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static t_data	data;
	t_node_list		*line;
	char			*result;

	result = NULL;
	line = ft_get_new_node(NULL);
	if (line)
	{
		ft_parse_line(fd, &data, line);
		if (line->data[0])
			result = ft_get_result(line);
		ft_free(line);
	}
	return (result);
}
