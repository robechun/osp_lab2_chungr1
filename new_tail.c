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
void deallocate(line_node *);
line_node* deallocateLineNode(line_node *);

int main(int argc, char*argv[]) {
	// Initialize variables to use for getline() and fopen()
	// TODO: add better comments
	FILE *fs;
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;
	size_t linesToRead = 5;
	size_t linesRead = 0;
	line_node *head = malloc(sizeof(line_node));
	line_node *cur = head;

	if (argc > 4) 			// Too many arguments, exit
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
		
		for (int i = 0; i < linesToRead; i++) {
			if (!cur) 
				return 0;

			fwrite(cur->gotLine, cur->length, 1, stdout);
			cur = deallocateLineNode(cur);
		}	
		
	}	
	else  
	{
		for (int i = 1; i < argc; i++) 
		{
			if (strcmp(argv[i], "-n") == 0 && i+1 < argc) 
			{
				// if you can find a . character
				//  must mean that it is the wrong order of arguments
				//  strrchr will return a pointer to the . character if found
				//  in which case you want to exit gracefully
				//  argv[i+1] is the string to be searched, '.' is the character to look for
				if (strrchr(argv[i+1], '.'))
				{
					printf("Arguments not in correct order");
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
			printf("Error opening file specified.\n");
			exit(EXIT_FAILURE);
		}
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

void deallocate(line_node *cur){
	while(cur) {
		cur = deallocateLineNode(cur);
	}
}

line_node* deallocateLineNode(line_node *node) {
	line_node *ret = node->next;
	free(node->gotLine);
	free(node);

	return ret;
}
