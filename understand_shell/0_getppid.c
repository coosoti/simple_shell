#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	pid_t parent_pid = getppid();

	printf("The Process Parent ID: %d\n", parent_pid);

	return (0);

}
