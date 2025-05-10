/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 12:51:23 by gonische          #+#    #+#             */
/*   Updated: 2025/05/09 12:51:23 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BVH_H
# define BVH_H

# include "aabb.h"
# include "object.h"
# include <stdbool.h>

typedef struct s_bvh_node
{
	t_aabb				box;
	const t_object		*objects;
	struct s_bvh_node	*left;
	struct s_bvh_node	*right;
}	t_bvh_node;

typedef bool	(*t_obj_comparator)(const t_object *, const t_object *);

t_obj_comparator	randomize_comparator(void);

bool				box_compare_is_less(
						const t_object *a,
						const t_object *b,
						int axis);

bool				box_x_compare_is_less(
						const t_object *a,
						const t_object *b);

bool				box_y_compare_is_less(
						const t_object *a,
						const t_object *b);

bool				box_z_compare_is_less(
						const t_object *a,
						const t_object *b);

void				merge_sort_objects_array(
						t_object **objects,
						int start,
						int end,
						t_obj_comparator comparator);

t_bvh_node			*create_tree(
						t_object **objects,
						int start,
						int end,
						int depth);

void				free_bvh_tree(t_bvh_node *tree);

void				print_tree(t_bvh_node *tree);

#endif // BVH_H