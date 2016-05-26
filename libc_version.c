#include<stdio.h>
#include<gnu/libc-version.h>
#include<stdlib.h>

int main(int argc, int *argv[])
{
	
	printf("GNU libc version: %s\n", gnu_get_libc_version());
	printf("GNU libc release: %s\n", gnu_get_libc_release());
	exit(EXIT_SUCCESS);
}
