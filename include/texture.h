#ifndef TEXTURE_H
# define TEXTURE_H

#define TEXTURE_SC 20.0

typedef struct s_plane t_plane;
typedef struct s_hit_record t_hit_record;
typedef struct s_scene t_scene;
typedef struct s_color t_color;

typedef struct s_texture
{
	int	height;
	int	width;
	int	*pixels;
}	t_texture;

t_texture	*parse_texture(t_scene *scene, char *filename);
t_color get_plane_color(
	const t_plane *plane,
	t_hit_record *rec
);

#endif // !TEXTURE_H
