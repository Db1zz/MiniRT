/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 16:45:20 by gonische          #+#    #+#             */
/*   Updated: 2024/11/14 22:54:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif // BUFFER_SIZE

# ifndef LINE_DATA_SIZE
#  define LINE_DATA_SIZE 1024
# endif // LINE_DATA_SIZE

# include <stdlib.h>
# include "../libft.h"

typedef struct t_data
{
	char	buffer[BUFFER_SIZE + 1];
	size_t	i;
	int		bytes_read;
	int		last_fd;
}	t_data;

typedef struct t_node_list
{
	char				*data;
	struct t_node_list	*next;
}	t_node_list;

t_node_list	*ft_get_new_node(char *data);

#endif // GET_NEXT_LINE_H
