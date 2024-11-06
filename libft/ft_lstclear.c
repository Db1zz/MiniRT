/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 13:51:45 by gonische          #+#    #+#             */
/*   Updated: 2024/09/29 01:18:30 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tail;

	while (*lst)
	{
		tail = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = tail;
	}
	free(*lst);
	*lst = NULL;
}
