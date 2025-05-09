#ifndef MINIRT_H
#define MINIRT_H

#include "scene.h"
#include "render.h"

#ifdef __APPLE__
#include "key_macos.h"
#elif __linux__
#include "key_linux.h"
#endif

typedef struct s_minirt_ctx
{
	t_scene scene;
} t_minirt_ctx;

int minirt_routine(int argc, char **argv);

#endif //	MINIRT_H
	   // fedia was herrr