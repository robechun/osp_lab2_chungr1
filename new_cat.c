#include <stdio.h>
#include <stdlib.h>

int main(int argc, char*argv[]) {
	// Initialize variables to use for getline() and fopen()
	FILE *fs;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	if (argc > 2) 			// Too many arguments, exit
	{
		printf("Too many arguments!\n");
		exit(EXIT_FAILURE);
	}

	if (argc == 1)			// Read from stdin instead of file 
	{
		while ((nread = getline(&line, &len, stdin)) != -1)			// keep reading until eof or error
			fwrite(line,nread,1,stdout);
	}	
	else 
	{
		fs = fopen(argv[1], "r");		// open the file of specified by user for read
		if (fs == NULL)					// fs failed to open, exit gracefully
		{
			printf("Error opening file specified.\n");
			exit(EXIT_FAILURE);
		}
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
				fwrite(line,nread,1,stdout);						// write contents of line to stdout
		
		fclose(fs);			// close the file stream
	}

	free(line);				// free allocated memory
	return 0;
}

