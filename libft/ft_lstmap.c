/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/15 14:02:17 by gonische          #+#    #+#             */
/*   Updated: 2024/06/20 20:30:43 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*result;
	t_list	*head;
	void	*content;

	result = NULL;
	if (!lst || !f || !del)
		return (result);
	while (lst)
	{
		content = f(lst->content);
		head = ft_lstnew(content);
		if (!head)
		{
			del(content);
			ft_lstclear(&result, del);
			return (NULL);
		}
		ft_lstadd_back(&result, head);
		lst = lst->next;
	}
	return (result);
}
