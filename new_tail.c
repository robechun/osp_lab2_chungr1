#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main(int argc, char*argv[]) {
	// Initialize variables to use for getline() and fopen()
	FILE *fs;
	char *line = NULL;
	char *buffer = "";
	size_t len = 0;
	ssize_t nread;

	if (argc > 5) 			// Too many arguments, exit
	{
		printf("Too many arguments!\n");
		exit(EXIT_FAILURE);
	}

	// if new_tail is invoked by itself,
	// read from stdin until ctrl-d
	// and print the last 5 messages
	if (argc == 1)
	{	
		int linesRead = 0;
		while ((nread = getline(&line, &len, stdin)) != -1)			// keep reading until eof or error
		{
			char *temp;
			if (linesRead == 5) {
				char *firstOcc = strpbrk(buffer, "\n");
				temp = malloc(strlen(line)+(strlen(buffer)-strlen(firstOcc))+1);		// malloc space for new line excluding oldest line
				strcpy(temp, firstOcc);
				strcat(temp, line);
			}
			else
			{
				temp = malloc(strlen(buffer)+strlen(line)+1);
				strcpy(temp, buffer);
				strcat(temp, line);
				linesRead++;
			}
		
			// free the dynamic memory that we allocated to do buffering
			free(buffer);
			buffer = temp;
			temp = NULL;
			
		}

		fwrite(buffer,strlen(buffer),1,stdout);
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

