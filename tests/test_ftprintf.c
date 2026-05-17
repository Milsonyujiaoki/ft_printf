#include "../include/ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int g_pass = 0;
static int g_fail = 0;

static void	check(const char *label, int got, int expected)
{
	if (got == expected)
	{
		printf("  [PASS] %-25s ret=%d\n", label, got);
		g_pass++;
	}
	else
	{
		printf("  [FAIL] %-25s got=%d  expected=%d\n", label, got, expected);
		g_fail++;
	}
}

int	main(void)
{
	int	r1;
	int	r2;
	int	x;

	printf("=== ft_printf vs printf ===\n\n");

	/* plain string */
	r2 = printf("hello world\n");
	r1 = ft_printf("hello world\n");
	check("plain string", r1, r2);

	/* %%  */
	r2 = printf("100%%\n");
	r1 = ft_printf("100%%\n");
	check("%%", r1, r2);

	/* %c */
	r2 = printf("%c\n", 'A');
	r1 = ft_printf("%c\n", 'A');
	check("%c", r1, r2);

	/* %s */
	r2 = printf("%s\n", "hello");
	r1 = ft_printf("%s\n", "hello");
	check("%s", r1, r2);

	/* %s NULL — ft_printf imprime "(null)", esperamos 7 chars ("(null)\n") */
	r1 = ft_printf("%s\n", (char *)NULL);
	check("%s NULL", r1, 7);

	/* %d positive */
	r2 = printf("%d\n", 42);
	r1 = ft_printf("%d\n", 42);
	check("%d positive", r1, r2);

	/* %d negative */
	r2 = printf("%d\n", -42);
	r1 = ft_printf("%d\n", -42);
	check("%d negative", r1, r2);

	/* %d zero */
	r2 = printf("%d\n", 0);
	r1 = ft_printf("%d\n", 0);
	check("%d zero", r1, r2);

	/* %i INT_MAX */
	r2 = printf("%i\n", INT_MAX);
	r1 = ft_printf("%i\n", INT_MAX);
	check("%i INT_MAX", r1, r2);

	/* %u */
	r2 = printf("%u\n", 4294967295U);
	r1 = ft_printf("%u\n", 4294967295U);
	check("%u UINT_MAX", r1, r2);

	/* %u zero */
	r2 = printf("%u\n", 0U);
	r1 = ft_printf("%u\n", 0U);
	check("%u zero", r1, r2);

	/* %x lowercase */
	r2 = printf("%x\n", 255);
	r1 = ft_printf("%x\n", 255);
	check("%x", r1, r2);

	/* %x zero */
	r2 = printf("%x\n", 0);
	r1 = ft_printf("%x\n", 0);
	check("%x zero", r1, r2);

	/* %X uppercase */
	r2 = printf("%X\n", 255);
	r1 = ft_printf("%X\n", 255);
	check("%X", r1, r2);

	/* %p */
	x = 0;
	r2 = printf("%p\n", (void *)&x);
	r1 = ft_printf("%p\n", (void *)&x);
	check("%p ret", r1, r2);

	/* mixed */
	r2 = printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	r1 = ft_printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	check("mixed specifiers", r1, r2);

	printf("\n=== %d passed, %d failed ===\n", g_pass, g_fail);
	return (g_fail > 0 ? 1 : 0);
}
