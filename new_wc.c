#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char*argv[]) {
	FILE *fs = stdin;									// File to be opened for write
	char *line = NULL;									// line used for getline
	size_t len = 0;										// length of line used for getline
	ssize_t nread;										// bytes read for getLine
	bool fileFound = false;								// flag to indicate if file is part of argv
	bool flagFound = false;								// flag to indicate if flag is part of argv
	bool lineFlag = false;								// flag to indicate the argv flag is -l
	size_t numOfLines = 0;								// number of lines read
	size_t numOfChars = 0;								// number of chars read
	size_t numOfWords = 0;								// number of words read


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
			// strcmp takes in two arguments, both "string"
			//  and compares them
			//  returns 0 if they are the same
			if ((!strcmp(argv[i], "-c")) || (!strcmp(argv[i], "-l")))
			{
				// If there are multiple flags, then exit gracefully
				if (flagFound)
				{
					printf("Please only specify one flag\n");
					exit(EXIT_FAILURE);
				}

				flagFound = true;

				// If the flag is regarding line,
				//  set the lineFlag to be true;
				//  Later if lineFlag is false, we can assume char flag was used
				if (strcmp(argv[i], "-l") == 0)
					lineFlag = true;
			
			}
			
			// strrchr takes in two arguments, *char and char
			//  The first argument is the string to be searched
			//  The second argument is the char to be looked for
			//  strrchr returns a pointer to the first occurance (backwards) matching 2nd arg
			// in our case, if you can find a dot, it corresponds to a file
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

				// fopen opens the file specified in the first argument
				//  2nd argument says that it's opened for read only
				//  returns NULL if can't open file
				//  else, returns a pointer to the file opened
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

		// getline reads the entire line from the filestream (fs)
		//  and stores that line in the first argument (line)
		//  returns number of characters read.
		//  if unsuccessful, returns -1.
		// read each line and get number of words/lines
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
		{
			bool ignore = true;							// flag for a "keepgoing" when we discern words

			// update line and char count
			numOfLines++;
			numOfChars += nread;

			// Go through the current line
			//  Get words with <space> and <newline> as delimeters
			for (int i = 0; i < nread; i++) 
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

		// Print correct output given the flag argument
		if (lineFlag) 
			printf("Number of Lines:%d\n", numOfLines);
		else
			printf("Number of Characters:%d\n", numOfChars);

		printf("Number of Words:%d\n", numOfWords);
		fclose(fs);			// close the file stream
	}

	return 0;
}

