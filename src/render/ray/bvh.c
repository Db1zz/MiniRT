/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bvh.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 02:22:36 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 02:22:36 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bvh.h"

#include "aabb.h" /* t_aabb */
#include "libft.h" /* ft_calloc() */

#include <stdlib.h> /* NULL | free() */

t_bvh_node	*init_bvh_node(
	const t_aabb *box,
	t_object *objects,
	t_bvh_node *left,
	t_bvh_node *right)
{
	t_bvh_node	*bvh_node;

	bvh_node = ft_calloc(1, sizeof(t_bvh_node));
	if (!bvh_node)
		return (NULL);
	if (box != NULL)
		bvh_node->box = *box;
	bvh_node->left = left;
	bvh_node->right = right;
	bvh_node->objects = objects;
	return (bvh_node);
}

t_bvh_node	*create_tree(t_object **objects, int start, int end, int depth)
{
	t_bvh_node	*tree;
	int			object_span;
	int			mid;

	object_span = end - start;
	tree = init_bvh_node(NULL, NULL, NULL, NULL);
	if (object_span == 0)
	{
		tree->objects = objects[start];
		tree->box = objects[start]->box;
	}
	else
	{
		merge_sort_objects_array(objects, start, end, randomize_comparator());
		mid = start + object_span / 2;
		tree->left = create_tree(objects, start, mid, depth + 1);
		tree->right = create_tree(objects, mid + 1, end, depth + 1);
	}
	if (tree->left && tree->right)
		tree->box = create_aabb_from_aabb(&tree->left->box, &tree->right->box);
	else if (tree->left)
		tree->box = tree->left->box;
	else if (tree->right)
		tree->box = tree->right->box;
	return (tree);
}

void	free_bvh_tree(t_bvh_node *tree)
{
	t_bvh_node	*left;
	t_bvh_node	*right;

	if (tree == NULL)
		return ;
	left = tree->left;
	right = tree->right;
	free(tree);
	free_bvh_tree(left);
	free_bvh_tree(right);
}
