#include "ft_printf.h"

int	print_str(va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
		str = "(null)";
	ft_putstr_fd(str, 1);
	return ((int)ft_strlen(str));
}