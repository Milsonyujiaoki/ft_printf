#include "../../include/ft_printf.h"

static int	put_spaces(int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		put_char_len(' ');
		i++;
	}
	return (count);
}

int	print_percent(t_format *fmt, va_list args)
{
	int	count;

	(void)args;
	count = 0;
	// 1. Se NÃO tiver alinhamento à esquerda, põe os espaços ANTES do '%'
	if (!fmt->left_align && fmt->width > 1)
		count += put_spaces(fmt->width - 1);

	// 2. Imprime o caractere '%' de fato
	put_char_len('%');
	count++;

	// 3. Se TIVER a flag '-' (alinhamento à esquerda), põe os espaços DEPOIS
	if (fmt->left_align && fmt->width > 1)
		count += put_spaces(fmt->width - 1);

	return (count);
}