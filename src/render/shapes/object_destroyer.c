/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_destroyer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:09:31 by gonische          #+#    #+#             */
/*   Updated: 2025/05/05 13:48:26 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "object.h"

#include <stdlib.h>

void	object_destroy_cylinder(t_object *cylinder_object)
{
	t_cylinder	*cylinder;

	cylinder = (t_cylinder *)cylinder_object->data;
	free(cylinder->caps[0].data);
	free(cylinder->caps[1].data);
	free(cylinder->caps);
	free(cylinder);
	free(cylinder_object);
}
