#include "../../include/ft_printf.h"

int	print_str(t_format *fmt, va_list args)
{
	char	*str;

	(void)fmt;
	str = va_arg(args, char *);
	return (put_str_len(str, -1));
}