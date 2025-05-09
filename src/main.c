// #include "libft.h" /* for tests only */

#ifdef BONUS
# include "minirt_bonus.h"

int main(int argc, char **argv)
{
	minirt_routine_bonus(argc, argv);
	return (EXIT_SUCCESS);
}

#else
# include "minirt.h" /* minirt_routine() */

int main(int argc, char **argv)
{
	minirt_routine(argc, argv);
	return (EXIT_SUCCESS);
}

#endif	// #ifdef BONUS
