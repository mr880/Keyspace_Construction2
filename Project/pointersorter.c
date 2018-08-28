
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <dirent.h>
#include "writefile.c"

int numTokens = 0;

typedef struct Node{
	char* word;
	char* filename;
	int count;
	struct Node* next;
} *node;

node head = NULL;

void swap(node ptr, node curr)
{
	printf("Attempting Swap!\n");
	int tcount = ptr->count;
	ptr->count = curr->count;
	curr->count = tcount;

	char*tfile;
	tfile = ptr->filename;
	ptr->filename = curr->filename;
	curr->filename = tfile;

	// char*tword;
	// strcpy(tfile, ptr->word);
	// strcpy(ptr->word, curr->word);
	// strcpy(curr->word, tword);
	printf("(Swap!)\n");
}

void countsort()
{
	//REMEMBER THE ISSUE WITH THE LAST NODE BEING PART OF A GROUP OF SIMILAR WORD NODES
	//CHECK TESTCODE.C

	//ALSO REMEMBER TO CHANGE TO LOWER CASE
	node ptr = head;
	node curr = head->next;
	int count = 0;
	node newptr = NULL;
	while(curr->next != NULL){


		
		
		if(strcmp(ptr->word, curr->word) != 0){
			printf("\tptr->word: %s\n\tcurr->word: %s\n\tstrcmp: %d\n", ptr->word, curr->word, strcmp(ptr->word, curr->word));
			
			curr = curr->next;
			ptr = ptr->next;
			
			
		}
		else
		{
			//printf("ptr->word: %s\n", ptr->word);
			newptr = ptr;
			count = 0;

			while(strcmp(ptr->word, curr->word) == 0 && curr->next != NULL)
			{
				
				printf("ptr->word: %s - curr->word: %s - ptr->count: %d - curr->count: %d (Match!)\n", ptr->word, curr->word, ptr->count, curr->count);
				if(ptr->count < curr->count)
				{
					printf("\tptr->count: %d - curr->count: %d\n", ptr->count, curr->count);
					swap(ptr, curr);
					
					
				}
				printf("y\n");                   
				ptr = ptr->next;
				curr = curr->next;

				//printf("\tCount: %d\n", count);
				
				printf("x\n");
				++count;
			}

			
			
			ptr = newptr;
			curr = newptr->next;
			
			
      
			printf("\tCount: %d\n", count);
			while(count > 0)
			{
				

				printf("inside second while loop - pword %s - cword %s - pcount: %d - ccount: %d\n", ptr->word, curr->word, ptr->count, curr->count);
				if(ptr->count < curr->count)
				{
					    
					swap(ptr, curr);
					
					
				}
				ptr = ptr->next;
				curr = curr->next;

				count--;
				
				

			}

			//printf("count: %d\n", count);
		}
		
	}

}

void writefile()
{
	node ptr = head;
	node curr = head->next;

	FILE * fPointer;
	fPointer = fopen("testfile.xml", "w");
	fprintf(fPointer, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
	fprintf(fPointer, "<fileIndex>\n");

	while(curr->next != NULL)
	{
		

		fprintf(fPointer, "\t<word text=\"%s\">\n", ptr->word);
		fprintf(fPointer, "\t\t<file name=\"%s\">%d</file>\n", ptr->filename, ptr->count);
		if(strcmp(curr->word, ptr->word) == 0){


			while(strcmp(curr->word, ptr->word) == 0)
			{
				
				fprintf(fPointer, "\t\t<file name=\"%s\">%d</file>\n", curr->filename, curr->count);

				ptr = ptr->next;
				curr = curr->next;

			}
			//fprintf(fPointer, "\t</word>\n");
			ptr = ptr->next;
			curr = curr->next;

		}
		else{
			ptr = ptr->next;
			curr = curr->next;
		}
		fprintf(fPointer, "\t</word>\n");

		
		

		
	}

	fprintf(fPointer, "</fileIndex>\n");
	fclose(fPointer);

	return;
}

node find(char* word, char* filename) {

   	//start from the first link
   	node current = head;

   	//if list is empty
   	if(head == NULL) {
      	return NULL;
   	}

   	//navigate through list
   	while( current != NULL) {
	
      	if(strcmp(current->word,word) == 0 && strcmp(current->filename,filename) == 0) {
      		current->count++;
         	return current;
     	}

        current = current->next;
      	
   	}
   	
   	
   	return NULL;
}

int length() {
   	int length = 0;
   	node current;
	
  	for(current = head; current != NULL; current = current->next) {
      	length++;
   	}
	
   	return length;
}

void sort() {

   	int i, j, k, tempCount;
   	char* tempWord;
   	char* tempFilename;
	node current;
   	node next;
	
   	int size = length();
   	k = size ;
	
   	for ( i = 0 ; i < size - 1 ; i++, k-- ) {
   	   	current = head;
    	next = head->next;
		
     	for ( j = 1 ; j < k ; j++ ) {   

         	if ( strcmp(current->word, next->word) > 0 ) {
	            tempWord = current->word;
	            current->word = next->word;
	            next->word = tempWord;

	            tempFilename = current->filename;
	            current->filename = next->filename;
	            next->filename = tempFilename;

	            tempCount = current->count;
	            current->count = next->count;
	            next->count = tempCount;
         	}
			
         	current = current->next;
        	next = next->next;
      	}
   	}   
}

void insertFirst(char* word, char* filename) {
   //create a link
	node test_node = find(word, filename);

	if(test_node == NULL){
		node new_node = (node) malloc(sizeof(struct Node));

		new_node->word = word;
		new_node->filename = filename;
		new_node->count = 1;

		//point it to old first node
		new_node->next = head;

		//point first to new first node
		head = new_node;
		printf("head->word: %s\n",head->word);
	}

	
	


	
}


void printList(node head) {
   node ptr = head;
   printf("\n[ ");
	
   //start from the beginning
   while(ptr != NULL) {
      printf("(%s,%s,%d)\n",ptr->word,ptr->filename,ptr->count);
      ptr = ptr->next;
   }
	
   printf(" ]");
}



int returnNumTokens(char* input)
{
	int count = 0; 

	if(isalpha(input[0]))
		count++;

	for(int j = 1; input[j]; j++)
	{
	
		if(input[j-1] == '-' && isalpha(input[j]))
			count++;
	
	}

	printf("---\nNumber of Tokens: %d\n", count);
	printf("---\n");
	return count;

}

void tokenArrayReturnsAlphaArray(char **arr, char* filename)
{

	
	

	for(int i = 0; i < numTokens; i++)
	{
		printf("arr[%d]: %s -- filename: %s\n", i, arr[i], filename);
		insertFirst(arr[i], filename);
		
		
		
	}



	return;
}

char* insertDelimeterReturnsString(const char* input)
{
	char* inputCopy = (char*) malloc(strlen(input)* sizeof(char));
	//char* inputCopy;

	for(int i = 0; i < strlen(input); i++)
	{
		if(!isalpha(input[i]))
			strcpy(&inputCopy[i],"-");
		else
			strcpy(&inputCopy[i], &input[i]);
	}             
	printf("%s\n", inputCopy);
	//free(inputCopy);
	return inputCopy;
}

char** inputStringReturnsTokenArray(char* input, int numTokens)
{	
	
	int i = 1;
	char* token;
	const char d[2] = "-";
	char **arr = (char**)malloc(numTokens * sizeof(char*));
	//char **arr;

	token = strtok(input, d);
	arr[0] = token;
	printf("arr[0]: %s\n", arr[0]);

	while(i < numTokens)
	{
		token = strtok(NULL, d);
		arr[i] = token;
		printf("arr[%d]: %s\n", i, arr[i]);
		i++;
	}

	
	return arr;
	
}

