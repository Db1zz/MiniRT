#ifndef FT_ERROR_H
# define FT_ERROR_H

# define ERR_NO_ERROR 0

# define STANDARD_ERROR_MIN 1
# define STANDARD_ERROR_MAX 20

# define PARSER_ERRN_MIN 21
# define PARSER_ERRN_MAX 42

# define MINIRT_ERRORN_MIN 43
# define MINIRT_ERRORN_MAX 64

/*
	Standard errors
*/
# define ERR_NULL_PARAMETER 1
# define ERR_MALLOC_FAILED 2
# define ERR_FAILED_TO_OPEN_FILE 3
# define ERR_INVALID_FUNC_ARGS 4

/*
	Parser error codes
*/
# define ERR_RATIO_RANGE_ERROR 21
# define ERR_TYPE_CONVERSION_FAILED 22
# define ERR_STRING_IS_NOT_NUM 23
# define ERR_SPLIT_FAILED 24
# define ERR_STR_TO_COLOR_FAILED 25
# define ERR_ATOI_FAILED 26
# define ERR_FAILED_TO_NORM_VECTOR 27
# define ERR_UNKNOWN_OBJECT_SPECIFIER 28
# define ERR_MULTIPLE_OBJECTS_INSTANCES 29
# define ERR_STR_TO_VECTOR_FAILED 30
# define ERR_CAMERA_NOT_FOUND 31
# define ERR_OBJECTS_AMOUNT_EXCEED_LIMITS 32
# define ERR_INVALID_FILE_EXTENSION 33
# define ERR_OPEN_TEXTURE_FAILURE 34

/*
	MiniRT error codes
*/
# define ERR_ARGC_ERROR 43
# define ERR_INCORRECT_COLOR_VALUES 44
# define ERR_INCORRECT_FOV_VALUE 45

typedef int	t_errorn;
typedef struct s_error
{
	t_errorn		errorn;
	const char		*func;
}	t_error;

void	ft_perror(t_errorn errorn, const char *func);
void	ft_display_error(const t_error *error);
void	set_error(t_error *error, t_errorn errorn, const char *func);
t_error	create_error(t_errorn errorn, const char *func);

#endif	// FT_ERROR_H
