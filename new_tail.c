#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct lineNode {
	char *gotLine;
	struct lineNode *prev;
	size_t length;
} line_node;

void deallocate(line_node *);
int main(int argc, char*argv[]) {
	// Initialize variables to use for getline() and fopen()
	FILE *fs;
	char *line = NULL;
	char **buffer = NULL;
	size_t bufferLen = 0;
	size_t len = 0;
	ssize_t nread;
	line_node *cur = NULL;

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
		while ((nread = getline(&line, &len, stdin)) != -1)			// keep reading until eof or error
		{
			// While you have valid input, allocate these "nodes" so that
			//  you store the line and information about the line.
			// This kind of works like a stack, where you only have a pointer to prev
			//  so that you traverse backwards
			line_node *newNode = malloc(sizeof(line_node));			
			newNode->gotLine = line;
			newNode->length = len;
			newNode->prev = cur;
			cur = newNode;	
			line = NULL;
		}
		
		for (int i = 0; i < 5; i++) {
			if (!cur)
				return 0;
			fwrite(cur->gotLine, cur->length, 1, stdout);
			free(cur->gotLine);
			line_node *temp = cur->prev;
			cur = cur->prev;
			temp = NULL;
		}
		deallocate(cur);
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

void deallocate(line_node *cur){
	while(cur) {
		free(cur->gotLine);
		line_node *temp = cur->prev;
		cur = cur->prev;
		temp = NULL;
	}

}
