#include "philo.h"

int main ()
{
	int a = 0;
	while(a < 4)
		printf("1 a = %d\n", a++);
	printf("AFTER 1 CYCLE a = %d\n", a);
	while(a--)
		printf("2 a = %d\n", a);
	printf("AFTER 2 CYCLE a = %d\n", a);
	return 1;
}