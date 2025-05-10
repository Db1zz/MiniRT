#include "bvh.h"

static void merge(
	t_object **objects_start,
	int left_size,
	int right_size,
	t_obj_comparator comparator)
{
	const int sorting_size = right_size + left_size;
	t_object *buffer[left_size + right_size];
	int i;
	int j;
	int k;

	if (left_size + right_size == 0)
		return;
	i = 0;
	j = 0;
	k = left_size;
	while (j < left_size && k < right_size + left_size)
	{
		if (comparator(objects_start[j], objects_start[k]))
			buffer[i] = objects_start[j++];
		else
			buffer[i] = objects_start[k++];
		++i;
	}
	while (j < left_size)
		buffer[i++] = objects_start[j++];
	while (k < left_size + right_size)
		buffer[i++] = objects_start[k++];
	i = 0;
	while (i < sorting_size)
	{
		objects_start[i] = buffer[i];
		++i;
	}
}

void merge_sort_objects_array(
	t_object **objects,
	int start,
	int end,
	t_obj_comparator comparator)
{
	int mittel;
	int left_size;
	int right_size;

	if (start >= end || end - start == 0)
		return;

	mittel = start + (end - start) / 2;
	left_size = mittel + 1 - start;
	right_size = end - mittel;
	merge_sort_objects_array(objects, start, mittel, comparator);
	merge_sort_objects_array(objects, mittel + 1, end, comparator);
	merge(&objects[start], left_size, right_size, comparator);
}
