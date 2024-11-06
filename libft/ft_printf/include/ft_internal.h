/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_internal.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gonische <gonische@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 16:54:30 by gonische          #+#    #+#             */
/*   Updated: 2024/09/27 23:00:03 by gonische         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_INTERNAL_H
# define FT_INTERNAL_H

/*
	Headers
*/
# include "../../libft.h"
# include "./ft_printf.h"
# include <stdlib.h>
# include <stdbool.h>
# include <stdarg.h>
# include <stdint.h>
# include <unistd.h>

/*
	Preprocessor definitions
*/
# define MAX_BUFFER_SIZE	32
# define MINUS_FLAG			1
# define ZERO_FLAG			2
# define DOT_FLAG			4
# define HASH_FLAG			8
# define SPACE_FLAG			16
# define PLUS_FLAG			32
# define WIDTH_FLAG			64
# define PATTERN_SIZE		6

/*
	Data type defenitions
*/
typedef struct t_format
{
	char	specifier;
	char	flags;
	int		width;
	int		precision;
	int		size;
	char	*output_str;
	char	*special_str;
}	t_format;

typedef int	(*t_disp_func)(t_format *, int);

/*
	Functions
*/
void		ft_set_bit(char *bit_set, char bit);
bool		ft_check_bit(char bit_set, char bit);
bool		ft_check_remove_bit(char *bit_set, char bit);
void		ft_adjust_bits(char *bit_set, char bits);
bool		ft_isspecifier(char c);
char		ft_isflag(char c);
void		ft_calc_width_precision(t_format *f);
void		ft_validate_flags(t_format *f);
size_t		ft_get_number_size(int64_t number);
void		ft_convert_to_address_str(t_format *f, uint64_t address);
void		ft_convert_to_number_str(t_format *f, int64_t number);
void		ft_convert_to_hex_str(t_format *f, uint32_t number);
void		ft_get_specifier(const char *str, t_format *f);
void		ft_get_special_str(t_format *f);
void		ft_get_output_str(va_list *data, t_format *f);
void		ft_get_flags(const char *str, t_format *f);
t_format	*ft_get_format_data(const char *str, va_list *data);
int			ft_display_padding(t_format *f, int fd);
int			ft_display_modifier(t_format *f, int fd);
int			ft_display_precision(t_format *f, int fd);
int			ft_display_str(t_format *f, int fd);
int			ft_display_format(t_format *f, int fd);
void		ft_calc_width_precision(t_format *f);
void		ft_validate_flags(t_format *f);
size_t		ft_get_number_size(int64_t number);
t_disp_func	*ft_get_pattern(t_format *f);
int			ft_printstr(char *str, int fd);
int			ft_get_hex_size(uint64_t hex);

#endif // FT_INTERNAL_H