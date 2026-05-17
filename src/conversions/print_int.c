#include "ft_printf.h"

int	print_int(va_list args)
{
	int		n;
	char	*s;
	int		len;

	n = va_arg(args, int);
	s = ft_itoa(n);
	len = (int)ft_strlen(s);
	ft_putstr_fd(s, 1);
	ft_free(s);
	return (len);
}