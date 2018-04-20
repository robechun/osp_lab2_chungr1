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
		// loop through all the arguments in argv
		//  and print it out exactly as so.
		for (int i = 1; i < argc; i++)
			printf("%s ", argv[i]);

		// print out newline at the end
		printf("\n");
	}

	return 0;
}

