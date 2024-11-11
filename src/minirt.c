/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gwagner <gwagner@student.42wolfsburg.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 08:27:44 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 16:49:50 by gwagner          ###   ########.fr       */
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
