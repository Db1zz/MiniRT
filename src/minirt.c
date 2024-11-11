/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:27:44 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 17:28:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dependencies.h"

int	main(/*int argc, char **argv*/)
{
	char	**data = ft_split("0,,", ',');
	int		i = 0;
	while (data[i])
		i++;
	printf("%d\n", i);
}
