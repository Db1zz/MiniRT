#include "minirt.h"
#include "texture.h"

t_color sphere_checkerboard(t_sphere *sphere, t_hit_record *rec)
{
    double sines;
    double checkerboard;
    t_vector unit_sphere;
    t_vector unit_sphere2;

    unit_sphere = vec3_normalize(rec->intersection_p);
    unit_sphere2 = vec3_normalize(rec->intersection_p);
    sines = sin(10 * unit_sphere.x) * sin(10 * unit_sphere.y) * sin(10 * unit_sphere.z);
    checkerboard = sines < 0 ? 1 : 0;
    if (checkerboard)
        return (create_color(0, 0, 0));
    else
        return (create_color(255, 255, 255));
}

t_color get_sphere_color(t_sphere *sphere, t_hit_record *rec)
{
    if (rec->obj_type == E_SPHERE && rec->texture_type == 1)
        return(sphere_checkerboard(sphere, rec));
    else
        return (rec->color);
}
