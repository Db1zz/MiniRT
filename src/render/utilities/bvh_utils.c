#include "bvh.h"
#include "minirt_math.h"

bool box_compare_is_less(const t_object *a, const t_object *b, int axis)
{
	return (a->box.interval[axis].min < b->box.interval[axis].min);
}

bool box_x_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 0));
}

bool box_y_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 1));
}

bool box_z_compare_is_less(const t_object *a, const t_object *b)
{
	return (box_compare_is_less(a, b, 2));
}

t_obj_comparator randomize_comparator()
{
	static const t_obj_comparator comparator_array[3] = {
		box_x_compare_is_less,
		box_y_compare_is_less,
		box_z_compare_is_less};

	return (comparator_array[rand_int(0, 2)]);
}
