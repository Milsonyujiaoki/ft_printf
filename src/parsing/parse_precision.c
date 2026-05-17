# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>

int	parse_precision(const char *fmt, t_format *format)
{
    int i = 0;

    if (fmt[i] == '.')
    {
        i++;
        format->precision = 0; // Se houver '.', mas sem número, a precisão é 0
        if (ft_isdigit(fmt[i]))
        {
            format->precision = ft_atoi(fmt + i);
            while (ft_isdigit(fmt[i]))
                i++;
        }
    }
    return (i);
}