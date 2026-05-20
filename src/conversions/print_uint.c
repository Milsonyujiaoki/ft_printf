#include "../../include/ft_printf.h"

static int	put_chars(char c, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		put_char_len(c);
		i++;
	}
	return (count);
}

// Calcula quantos dígitos o número unsigned vai ocupar
static int	get_uint_digits(unsigned int n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		digits++;
		n /= 10;
	}
	return (digits);
}

// Imprime o número puro sem recursão complexa no retorno
static void	put_uint_pure(unsigned int n)
{
	if (n >= 10)
		put_uint_pure(n / 10);
	put_char_len((n % 10) + '0');
}

int	print_uint(t_format *fmt, va_list args)
{
	unsigned int	n;
	int				digits;
	int				zeros;
	int				total_len;
	int				count;

	n = va_arg(args, unsigned int);
	digits = get_uint_digits(n);

	// 1. Caso especial: precisão 0 com valor 0 não exibe nada
	if (fmt->precision == 0 && n == 0)
		digits = 0;

	// 2. Calcula os zeros exigidos pela precisão
	zeros = 0;
	if (fmt->precision > digits)
		zeros = fmt->precision - digits;

	// 3. Calcula o tamanho total final do bloco na tela
	total_len = digits + zeros;

	count = 0;
	// 4. Largura à direita: Espaços ANTES se não houver flag '-'
	if (!fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	// 5. Imprime os zeros da precisão
	if (zeros > 0)
		count += put_chars('0', zeros);

	// 6. Imprime os dígitos do número
	if (digits > 0)
		put_uint_pure(n);

	// 7. Largura à esquerda: Espaços DEPOIS se a flag '-' estiver ativa
	if (fmt->left_align && fmt->width > total_len)
		count += put_chars(' ', fmt->width - total_len);

	return (count + total_len);
}