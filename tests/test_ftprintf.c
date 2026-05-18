#include "../include/ft_printf.h"
#include <stdio.h>
#include <limits.h>

static int g_pass = 0;
static int g_fail = 0;

static void	check(const char *label, int got, int expected)
{
	if (got == expected)
	{
		printf("  [PASS] %-30s ret=%d\n", label, got);
		g_pass++;
	}
	else
	{
		printf("  [FAIL] %-30s got=%d  expected=%d\n", label, got, expected);
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
	printf("--- Plain String ---\n");
	r2 = printf("hello world\n");
	r1 = ft_printf("hello world\n");
	check("plain string", r1, r2);

	/* %%  */
	printf("\n--- Percent Sign ---\n");
	r2 = printf("100%%\n");
	r1 = ft_printf("100%%\n");
	check("%%", r1, r2);

	r2 = printf("%%%%\n");
	r1 = ft_printf("%%%%\n");
	check("%%%% (double)", r1, r2);

	/* %c */
	printf("\n--- Character (%c) ---\n");
	r2 = printf("%c\n", 'A');
	r1 = ft_printf("%c\n", 'A');
	check("%c 'A'", r1, r2);

	r2 = printf("%c\n", '\0');
	r1 = ft_printf("%c\n", '\0');
	check("%c '\\0'", r1, r2);

	r2 = printf("%c%c%c\n", 'a', 'b', 'c');
	r1 = ft_printf("%c%c%c\n", 'a', 'b', 'c');
	check("%c multiple", r1, r2);

	/* %s */
	printf("\n--- String (%s) ---\n");
	r2 = printf("%s\n", "hello");
	r1 = ft_printf("%s\n", "hello");
	check("%s 'hello'", r1, r2);

	r2 = printf("%s\n", "");
	r1 = ft_printf("%s\n", "");
	check("%s empty string", r1, r2);

	r1 = ft_printf("%s\n", (char *)NULL);
	check("%s NULL", r1, 7);

	/* %d and %i */
	printf("\n--- Signed Integer (%d/%i) ---\n");
	r2 = printf("%d\n", 42);
	r1 = ft_printf("%d\n", 42);
	check("%d positive (42)", r1, r2);

	r2 = printf("%d\n", -42);
	r1 = ft_printf("%d\n", -42);
	check("%d negative (-42)", r1, r2);

	r2 = printf("%d\n", 0);
	r1 = ft_printf("%d\n", 0);
	check("%d zero", r1, r2);

	r2 = printf("%i\n", INT_MAX);
	r1 = ft_printf("%i\n", INT_MAX);
	check("%i INT_MAX", r1, r2);

	r2 = printf("%i\n", INT_MIN);
	r1 = ft_printf("%i\n", INT_MIN);
	check("%i INT_MIN", r1, r2);

	r2 = printf("%d\n", -2147483648);
	r1 = ft_printf("%d\n", -2147483648);
	check("%d -2147483648", r1, r2);

	/* %u */
	printf("\n--- Unsigned Integer (%u) ---\n");
	r2 = printf("%u\n", 4294967295U);
	r1 = ft_printf("%u\n", 4294967295U);
	check("%u UINT_MAX", r1, r2);

	r2 = printf("%u\n", 0U);
	r1 = ft_printf("%u\n", 0U);
	check("%u zero", r1, r2);

	r2 = printf("%u\n", 123456U);
	r1 = ft_printf("%u\n", 123456U);
	check("%u 123456", r1, r2);

	/* %x lowercase */
	printf("\n--- Hexadecimal Lowercase (%x) ---\n");
	r2 = printf("%x\n", 255);
	r1 = ft_printf("%x\n", 255);
	check("%x 255 (ff)", r1, r2);

	r2 = printf("%x\n", 0);
	r1 = ft_printf("%x\n", 0);
	check("%x zero", r1, r2);

	r2 = printf("%x\n", 16);
	r1 = ft_printf("%x\n", 16);
	check("%x 16 (10)", r1, r2);

	r2 = printf("%x\n", UINT_MAX);
	r1 = ft_printf("%x\n", UINT_MAX);
	check("%x UINT_MAX", r1, r2);

	/* %X uppercase */
	printf("\n--- Hexadecimal Uppercase (%X) ---\n");
	r2 = printf("%X\n", 255);
	r1 = ft_printf("%X\n", 255);
	check("%X 255 (FF)", r1, r2);

	r2 = printf("%X\n", 0);
	r1 = ft_printf("%X\n", 0);
	check("%X zero", r1, r2);

	r2 = printf("%X\n", UINT_MAX);
	r1 = ft_printf("%X\n", UINT_MAX);
	check("%X UINT_MAX", r1, r2);

	/* %p */
	printf("\n--- Pointer (%p) ---\n");
	x = 0;
	r2 = printf("%p\n", (void *)&x);
	r1 = ft_printf("%p\n", (void *)&x);
	check("%p &x", r1, r2);

	r2 = printf("%p\n", (void *)NULL);
	r1 = ft_printf("%p\n", (void *)NULL);
	check("%p NULL", r1, r2);

	r2 = printf("%p\n", (void *)0x12345678);
	r1 = ft_printf("%p\n", (void *)0x12345678);
	check("%p 0x12345678", r1, r2);

	/* mixed */
	printf("\n--- Mixed Specifiers ---\n");
	r2 = printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	r1 = ft_printf("n=%d s=%s c=%c\n", 7, "ok", '!');
	check("mixed specifiers", r1, r2);

	r2 = printf("%s %d %x %p\n", "test", -42, 255, (void *)&x);
	r1 = ft_printf("%s %d %x %p\n", "test", -42, 255, (void *)&x);
	check("complex mix", r1, r2);

	r2 = printf("%c%s%d%u%x%X%p%%\n", 'A', "B", 1, 2U, 3, 4, (void *)&x);
	r1 = ft_printf("%c%s%d%u%x%X%p%%\n", 'A', "B", 1, 2U, 3, 4, (void *)&x);
	check("all specifiers", r1, r2);

	/* edge cases */
	printf("\n--- Edge Cases ---\n");
	r2 = printf("\n");
	r1 = ft_printf("\n");
	check("just newline", r1, r2);

	r2 = printf("");
	r1 = ft_printf("");
	check("empty format", r1, r2);

	r2 = printf("no specifiers at all");
	r1 = ft_printf("no specifiers at all");
	check("no specifiers", r1, r2);

	printf("\n===========================================\n");
	printf("=== RESULTADO: %d PASSED, %d FAILED ===\n", g_pass, g_fail);
	printf("===========================================\n");
	
	return (g_fail > 0 ? 1 : 0);
}
