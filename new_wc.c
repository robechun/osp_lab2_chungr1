#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char*argv[]) {
	FILE *fs = stdin;									// File to be opened for write
	char *line = NULL;									// line used for getline
	size_t len = 0;										// length of line used for getline
	ssize_t nread;										// bytes read for getLine
	bool fileFound = false;
	bool flagFound = false;
	bool lineFlag = false;
	size_t numOfLines = 0;
	size_t numOfChars = 0;
	size_t numOfWords = 0;
	

	if (argc > 3) 			// Too many arguments, exit
	{
		printf("Too many arguments!\n");
		exit(EXIT_FAILURE);
	}
	else  
	{
		// If invoked by itself without flags, we exit gracefully
		if (argc == 1) {
			printf("Not enough arguments\n");
			exit(EXIT_FAILURE);
		}
		// Loop through each argument to get correct idea of what the arguments should be.
		for (int i = 1; i < argc; i++) 
		{
			if ((!strcmp(argv[i], "-c")) || (!strcmp(argv[i], "-l")))
			{
				if (flagFound)
				{
					printf("Please only specify one flag\n");
					exit(EXIT_FAILURE);
				}

				flagFound = true;
				// If the flag is regarding line,
				//  set the lineFlag to be true;
				if (strcmp(argv[i], "-l") == 0)
					lineFlag = true;
			
			}
			
			// If you can find a dot, it corresponds to a file
			if (strrchr(argv[i], '.'))
			{
				// If more than one file is specified, exit gracefully
				if (fileFound)
				{
					fclose(fs);
					printf("Please specify only one file\n");
					exit(EXIT_FAILURE);
				}
				fileFound = true;
				fs = fopen(argv[i], "r");
			}
		}	
	
		// fs failed to open, exit gracefully.
		if (fs == NULL)
		{
			printf("Error opening file specified.\n");
			exit(EXIT_FAILURE);
		}

		// If no flags are found, exit gracefully.
		if (!flagFound) 
		{
			printf("Error discerning flags.\n");
			exit(EXIT_FAILURE);
		}

		// read each line and get number of words/lines
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
		{
			size_t lineLength = strlen(line);
			bool ignore = true;
			// if successfully read, increment numOfLines by 1
			numOfLines++;
			numOfChars += lineLength;
			// Go through the returned line and count # of characters and words
			for (int i = 0; i < lineLength; i++) 
			{
				if (line[i] == ' ' || line[i] == '\n') 
					ignore = true;
				else if (ignore)
				{
					ignore = false;
					numOfWords++;
				}
			}
		}

		if (lineFlag) 
			printf("Number of Lines:%d\n", numOfLines);
		else
			printf("Number of Characters:%d\n", numOfChars);

		printf("Number of Words:%d\n", numOfWords);
		fclose(fs);			// close the file stream
	}

	return 0;
}

