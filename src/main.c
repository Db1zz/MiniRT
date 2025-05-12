/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 01:02:28 by gonische          #+#    #+#             */
/*   Updated: 2025/05/10 01:02:28 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "minirt_bonus.h" /* minirt_routine_bonus */
#else
# include "minirt.h" /* minirt_routine() */
#endif // ifdef BONUS

// #include "libft.h" /* for tests only */

#ifdef BONUS

int	main(int argc, char **argv)
{
	minirt_routine_bonus(argc, argv);
	return (EXIT_SUCCESS);
}

#else

int	main(int argc, char **argv)
{
	minirt_routine(argc, argv);
	return (EXIT_SUCCESS);
}

#endif	// #ifdef BONUS
