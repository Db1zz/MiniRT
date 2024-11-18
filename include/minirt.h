#ifndef MINIRT_H
# define MINIRT_H

# include "ft_error.h"
# include "parser.h"
# include "dependencies.h"
# include <stdlib.h>

#ifdef __APPLE__
	# include "keu_macos.h"
#elif __linux__
	# include "key_linux.h"
#endif

void	free_2dmatrix(char **matrix);
bool	is_string_number(char *line);
size_t	get_2dmatrix_size(char **matrix);
bool	check_str_numbers(char **numbers, int expected_size);

#endif //	MINIRT_H
