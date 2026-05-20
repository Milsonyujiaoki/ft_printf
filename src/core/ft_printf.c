#include "ft_printf.h"

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
	format->precision = 0;
	format->zero = 0;
	format->left_align = 0;
	format->plus = 0;
	format->space = 0;
	format->hash = 0;
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
		}
		else
		{
			i++;
			if (!fmt[i])
				break ;
			init_format(&format);
			format.specifier = fmt[i];
			count += dispatch(&format, args);
		}
		i++;
	}
	va_end(args);
	return (count);
}