#include "texture.h" 
#include "mlx.h"
#include "scene.h"

t_texture	parse_texture(t_scene* scene, char* filename) {
	t_texture texture;
	void* img;

	img = mlx_xpm_file_to_image(scene->mlx, filename, &texture.width, &texture.height); 
	texture.pixels = (int*)mlx_get_data_addr(img, NULL, NULL, NULL);
	mlx_destroy_image(scene->mlx, img);
	return (texture);
}
