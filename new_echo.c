#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {
	// If only one argument, print out a newline and exit.
	if (argc == 1)
	{
		printf("\n");
		return 0;
	}	
	else 
	{
		for (int i = 1; i < argc; i++)
			printf("%s ", argv[i]);

		printf("\n");
	}

	return 0;
}

