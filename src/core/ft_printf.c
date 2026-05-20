#include "../include/ft_printf.h"

static const t_dispatch	g_dispatch[] = {
	{SP_CHAR, print_char},
	{SP_STR, print_str},
	{SP_DEC, print_int},
	{SP_INT, print_int},
	{SP_HEX_LOW, print_hex},
	{SP_HEX_UP, print_hex},
	{SP_UINT, print_uint},
	{SP_PTR, print_ptr},
	{SP_PERCENT, print_percent},
};

static int	dispatch(t_format *fmt, va_list args)
{
	size_t	i;
	size_t	dispatch_size;

	i = 0;
	dispatch_size = sizeof(g_dispatch) / sizeof(g_dispatch[0]);
	while (i < dispatch_size)
	{
		if (g_dispatch[i].specifier == fmt->specifier)
			return (g_dispatch[i].fn(fmt, args));
		i++;
	}
	return (0);
}

static void	init_format(t_format *format)
{
	format->specifier = 0;
	format->width = 0;
	format->precision = -1; // -1 indica que a precisão não foi especificada
	format->zero = 0;
	format->left_align = 0;
	format->plus = 0;
	format->space = 0;
	format->hash = 0;
}

static void	parse_flags(const char *fmt, int *i, t_format *format)
{
    while (fmt[*i] == '0' || fmt[*i] == '-' || fmt[*i] == '+' ||
        fmt[*i] == ' ' || fmt[*i] == '#')
    {
        if (fmt[*i] == '0')
            format->zero = 1;
        else if (fmt[*i] == '-')
            format->left_align = 1;
        else if (fmt[*i] == '+')
            format->plus = 1;
        else if (fmt[*i] == ' ')
            format->space = 1;
        else if (fmt[*i] == '#')
            format->hash = 1;
        (*i)++;
    }
}

static void	parse_precision(const char *fmt, int *i, t_format *format, va_list args)
{
	if (fmt[*i] == '.')
	{
		(*i)++;
		format->precision = 0; /* Encontrou o ponto, o padrão agora vira 0 */
		if (fmt[*i] == '*')
		{
			format->precision = va_arg(args, int);
			(*i)++;
		}
		else
		{
			while (ft_isdigit(fmt[*i]))
			{
				format->precision = format->precision * 10 + (fmt[*i] - '0');
				(*i)++;
			}
		}
	}
}

static void    parse_specifier(const char *fmt, int *i, t_format *format)
{
    char c = fmt[*i];
    if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' ||
        c == 'u' || c == 'x' || c == 'X' || c == '%')
    {
        format->specifier = c;
        (*i)++;
    }
}

static void	parse_width(const char *fmt, int *i, t_format *format, va_list args)
{
    if (fmt[*i] == '*')
    {
        format->width = va_arg(args, int);
        (*i)++;
    }
    else
    {
        while (ft_isdigit(fmt[*i]))
        {
            format->width = format->width * 10 + (fmt[*i] - '0');
            (*i)++;
        }
    }
}

int	ft_printf(const char *fmt, ...)
{
	va_list		args;
	t_format	format;
	int			count;
	int			i;

	if (!fmt)
		return (-1);
	va_start(args, fmt);
	count = 0;
	i = 0;
	while (fmt[i])
	{
		if (fmt[i] != '%')
		{
			count += put_char_len(fmt[i]);
			i++; /* Incrementa apenas quando consome um caractere normal */
		}
		else
		{
			i++; /* Avança o '%' */
			if (!fmt[i])
				break ;
			init_format(&format);

			parse_flags(fmt, &i, &format);
			parse_width(fmt, &i, &format, args);
			parse_precision(fmt, &i, &format, args);
			parse_specifier(fmt, &i, &format);

			count += dispatch(&format, args);
		}
	}
	va_end(args);
	return (count);
}