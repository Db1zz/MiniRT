#ifndef REFLECTIONS_H
# define REFLECTIONS_H

#include "color.h"
#include "ray.h"
#include "object.h"

# define REFLECTION_MAX_DEPTH 100

t_color	send_reflection_ray(
	const t_object_list		*objects,
	const t_ray				*camera_ray,
	const t_ray_properties	*prop,
	const t_hit_record		*hit_rec);

#endif	// REFLECTIONS_H