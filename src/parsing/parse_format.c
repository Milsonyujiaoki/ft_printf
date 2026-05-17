# include "ft_printf.h"
# include "libft.h"
# include <stdarg.h>


int	parse_format(const char *fmt, t_format *format)
{
    int i = 0;

    // Inicializa o formato com valores padrão
    format->specifier = 0;
    format->width = 0;
    format->precision = -1; // -1 indica que a precisão não foi especificada
    format->zero = 0;
    format->left_align = 0;
    format->hash = 0;
    format->plus = 0;
    format->space = 0;

    // Parseia flags
    i += parse_flags(fmt + i, format);
    // Parseia largura
    i += parse_width(fmt + i, format);
    // Parseia precisão
    i += parse_precision(fmt + i, format);
    // Parseia especificador
    i += parse_specifier(fmt + i, format);

    return (i);
}