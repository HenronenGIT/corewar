#include <stdio.h>
# define MEM_SIZE	4096
# define IDX_MOD	(MEM_SIZE / 8)

//just a little tester thing
int main ()
{
	int pos = 0;
	int change = 4095;
	/*
	printf("pos + change: %d\n", pos + change);
	if (pos + change < 0)
		printf("%d\n", MEM_SIZE + (pos + change));
	else

	printf("%d \n", (pos + change) % MEM_SIZE);
	*/
	//test IDX_MOD
	printf("pos + change: %d\n", pos + change);
	printf("pos + change %% IDX_MOD: %d\n", (pos + change % IDX_MOD));

	return 0;
}