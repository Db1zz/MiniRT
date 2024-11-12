/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 11:46:08 by gonische          #+#    #+#             */
/*   Updated: 2024/11/11 22:42:25 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
#define MINIRT_H

#include "parser.h"
#include "dependencies.h"

void	free_2dmatrix(char **matrix);
bool	is_string_number(char *line);
size_t	get_2dmatrix_size(char **matrix);
bool	check_str_numbers(const char **numbers, int expected_size);
void	*ft_malloc(size_t size);

#endif //	MINIRT_H
