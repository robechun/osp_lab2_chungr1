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
	
	// If there's only one argument
	// We read from stdin instead of file
	if (argc == 1)	
	{
		// getline reads the entire line from the filestream (fs)
		//  and stores that line in the first argument (line)
		//  returns number of characters read.
		//  if unsuccessful, returns -1.
		// read each line and get number of words/lines
		while ((nread = getline(&line, &len, stdin)) != -1)			// keep reading until eof or error
		{
			// fwrite writes the contents of line, with # of bytes to write specified by nread
			//  of size 1 to stdout
			fwrite(line,nread,1,stdout);			
		}
	}	
	else 
	{
		// fopen opens the file specified in the first argument
		//  2nd argument says that it's opened for read only
		//  returns NULL if can't open file
		//  else, returns a pointer to the file opened
		fs = fopen(argv[1], "r");		// open the file of specified by user for read
		if (fs == NULL)					// fs failed to open, exit gracefully
		{
			printf("Error opening file specified.\n");
			exit(EXIT_FAILURE);
		}
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
		{
			fwrite(line,nread,1,stdout);						// write contents of line to stdout
		}	
		
		free(line);			// free dynamic memory
		fclose(fs);			// close the file stream
	}

	return 0;
}

