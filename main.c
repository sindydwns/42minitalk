#include <stdio.h>
#include <unistd.h>

int main()
{
	int n = 0b100000000;
	unsigned char *ptr = &n;

	for(int i = 0; i < 4; i++)
	{
		printf("%d\n", *ptr);
		ptr++;
	}
}