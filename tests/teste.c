#include <stdio.h>

int	main(void)
{
	char	*c;

	char d = 0xFF;
	c = &d;
	printf("%c\n", *c);
}