#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// LineNode definition
typedef struct lineNode {
	char *gotLine;			// the line got
	struct lineNode *next;	// the next node pointer
	size_t length;			// lenght of line
} line_node;

// Function prototypes
line_node* deallocateLineNode(line_node *);

int main(int argc, char*argv[]) {
	FILE *fs;											// File to be opened for write
	char *line = NULL;									// line used for getline
	size_t len = 0;										// length of line used for getline
	ssize_t nread;										// bytes read for getLine
	size_t linesToRead = 5;								// lines to read specified by -n (N)
	size_t linesRead = 0;								// Number of lines read
	line_node *head = malloc(sizeof(line_node));		// dummy head pointer for the linked-list
	line_node *cur = head;								// cur pointer for traversing

	if (argc > 4) 			// Too many arguments, exit
	{
		fprintf(stderr, "Too many arguments!\n");
		exit(EXIT_FAILURE);
	}
	else  
	{
		// if new_tail is invoked by itself,
		// read from stdin until ctrl-d
		// and print the last 5 messages
		if (argc == 1)
			fs = stdin;
		
		// Loop through each argument to get correct idea of what the arguments should be.
		// If argc == 1, this loop will not trigger
		for (int i = 1; i < argc; i++) 
		{
			// strcmp takes in two arguments, both "string"
		    //  and compares them
			//  returns 0 if they are the same
			if (strcmp(argv[i], "-n") == 0 && i+1 < argc) 
			{
				// if you can find a . character
				//  must mean that it is the wrong order of arguments
				//  strrchr will return a pointer to the . character if found
				//  in which case you want to exit gracefully
				//  argv[i+1] is the string to be searched, '.' is the character to look for
				if (strrchr(argv[i+1], '.'))
				{
					fprintf(stderr, "Arguments not in correct order\n");
					exit(EXIT_FAILURE);
				}
				linesToRead = atoi(argv[i+1]);
			}
		
			// If you can find a dot, it corresponds to a file
			if (strrchr(argv[i], '.'))
				fs = fopen(argv[i], "r");
		}	
			
		if (fs == NULL)					// fs failed to open, exit gracefully
		{
			fprintf(stderr, "Error opening file specified.\n");
			exit(EXIT_FAILURE);
		}

		// ************ BUFFERING *************** // 
		while ((nread = getline(&line, &len, fs)) != -1) 			// keep reading until eof or error
		{
			// While you have valid input, allocate these "nodes" so that
			//  you store the line and information about the line.
			// This linked list is prepared so that you can traverse it later.
			line_node *newNode = malloc(sizeof(line_node));			
			newNode->gotLine = line;
			newNode->length = len;
			cur->next = newNode;
			cur = cur->next;
			line = NULL;
			linesRead++;
			
			// if you exceed the # of lines to read,
			// deallocate the head, but make sure to adjust accordingly
			if (linesRead >= linesToRead) {
				head = deallocateLineNode(head);
			}	
		}
	
		// re-adjust cur pointer if there are less than 5 lines read
		//  This is because we have a dummy node at head in the beginning
		if (linesRead < linesToRead)
			cur = head->next;
		else
			cur = head;
	
		// Print out the results in the buffer
		// Also free up memory as you go
		for (int i = 0; i < linesToRead; i++) {
			if (!cur) 
				return 0;

			fwrite(cur->gotLine, cur->length, 1, stdout);
			cur = deallocateLineNode(cur);
		}	
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
