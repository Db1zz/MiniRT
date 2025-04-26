#include "bvh.h"
#include "aabb.h"
#include "object.h"
#include "libft.h"
#include <stdlib.h>

static void	print_spaces(int x)
{
	int i = 0;

	while (i++ < x)
		printf(" ");
}

static void	print_tree_line(
	const char *tree_symbol, const char *node_str, int level, char *buffer)
{
	int i;
	int spaces_consumed;
	int printed;

	i = 0;
	printed = 0;
	spaces_consumed = 0;
	while (i < level)
	{
		if (buffer[i] != ':')
		{
			printed += printf("%c", buffer[i]);
			spaces_consumed += printf(" ");
		}
		else
			spaces_consumed += printf("  ");
		++i;
	}
	print_spaces((level - spaces_consumed + (level - printed)));
	printf("%s%s", tree_symbol, node_str);
}

static void	print_tree_routine(
	t_bvh_node *tree, int level, char *buffer, size_t buffer_size)
{
	if (tree == NULL)
		return;

	if (tree->left && tree->right)
	{
		print_tree_line("|-", "N\n", level, buffer);
		buffer[level] = '|';
		print_tree_routine(tree->left, level + 1, buffer, buffer_size);
	}
	if (tree->objects) {
		print_tree_line("└─", tree->objects->type_name, level, buffer);
		printf(": %zu\n", tree->objects->id);
	}
	else
	{
		print_tree_line("└─", "N\n", level, buffer);
		if (tree->right)
			print_tree_routine(tree->right, level + 1, buffer, buffer_size);
		else
			print_tree_routine(tree->left, level + 1, buffer, buffer_size);
	}
	if (level - 1 >= 0)
		buffer[level - 1] = ':';
}

void	print_tree(t_bvh_node *tree)
{
	size_t buffer_size = 1024;
	char buffer[buffer_size + 1];
	buffer[0] = '\0';
	printf("N\n");
	print_tree_routine(tree, 0, buffer, buffer_size);
}
