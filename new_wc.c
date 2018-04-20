#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// LineNode definition
typedef struct lineNode {
	char *gotLine;			// the line got
	struct lineNode *next;	// the next node pointer
	size_t length;			// lenght of line
} line_node;

// Function prototypes
line_node* deallocateLineNode(line_node *);

int main(int argc, char*argv[]) {
	FILE *fs = stdout;									// File to be opened for write
	char *line = NULL;									// line used for getline
	size_t len = 0;										// length of line used for getline
	ssize_t nread;										// bytes read for getLine
	size_t linesToRead = 5;								// lines to read specified by -n (N)
	size_t linesRead = 0;								// Number of lines read
	line_node *head = malloc(sizeof(line_node));		// dummy head pointer for the linked-list
	line_node *cur = head;								// cur pointer for traversing
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
			printf("No flags specified\n");
			exit(EXIT_FAILURE);
		}

		// read each line and get number of words/lines
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
		{
			// if successfully read, increment numOfLines by 1
			numOfLines++;

			// Go through the returned line and count # of characters and words
			printf("len=%d\n",len);
			for (int i = 0; i < len; i++) 
			{
				numOfChars++;
				if (line[i] == ' ' || line[i] == '\n') 
				{
					while (line[i] == ' ' || line[i] == '\n') { i++; }
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

// deallocateLineNode takes in a line_node pointer
//  and deallocates dynamic memory inside the struct
//  as well as the node itself.
// Returns: the pointer pointing to the next node of the passed in node.
line_node* deallocateLineNode(line_node *node) {
	line_node *ret = node->next;
	free(node->gotLine);
	free(node);

	return ret;
}
