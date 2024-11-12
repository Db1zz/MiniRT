#ifndef LIGHT_H
#define LIGHT_H

#include "vector.h"
#include "color.h"
#include "scene.h"

#define RATIO_MIN 0
#define RATIO_MAX 1

typedef struct s_amb_lighting
{
	double	ratio;
	t_color	color;
}	t_amb_lighting;

typedef struct s_light
{
	t_vector	vector;
	double	ratio;
	t_color	color;
}	t_light;



void	create_light(t_scene *scene, const t_vector *vector,
			double ratio, const t_color *color);
void	create_amb_lightning(t_scene *scene,
			double ratio, const t_color *color);

#endif	// LIGHT_H
