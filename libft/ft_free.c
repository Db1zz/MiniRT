#include "libft.h"

#include <stdlib.h>

void	ft_free(void **data)
{
	free(data);
	*data = NULL;
}
