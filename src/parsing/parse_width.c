#include "ft_printf.h"
#include "libft.h"
#include <stdarg.h>


int	parse_width(const char *fmt, t_format *format)
{
    int i = 0;

    if (ft_isdigit(fmt[i]))
    {
        format->width = ft_atoi(fmt + i);
        while (ft_isdigit(fmt[i]))
            i++;
    }
    return (i);
}