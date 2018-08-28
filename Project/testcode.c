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

typedef struct Node{
	char* word;
	char* filename;
	int count;
	struct Node* next;
} *node;

node head = NULL;

void swap(node ptr, node curr)
{
	//printf("swap1!\n");
	int tcount = ptr->count;
	ptr->count = curr->count;
	curr->count = tcount;
	//printf("swap2!\n");
	char*tfile;
	tfile = ptr->filename;
	ptr->filename = curr->filename;
	curr->filename = tfile;
	printf("(swap!)\n");

	// char*tword;
	// strcpy(tfile, ptr->word);
	// strcpy(ptr->word, curr->word);
	// strcpy(curr->word, tword);
	
}

void sort()
{
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
				

				printf("inside second while loop - pword %s - cword %s - count: %d\n", ptr->word, curr->word, count);
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

void insertFirst(char* word, char* filename, int count) {
   //create a link



	node new_node = (node) malloc(sizeof(struct Node));

	new_node->word = word;
	new_node->filename = filename;
	new_node->count = count;

	//point it to old first node
	new_node->next = head;

	//point first to new first node
	head = new_node;
	//printf("head->word: %s\n",head->word);
	
}

void printList(node head) {
   	node ptr = head;
   	//printf("\n[ ");
	
   	//start from the beginning
   	printf("HEAD -> ");
   	while(ptr != NULL) {
      	printf("[%s,%s,%d] -> ",ptr->word,ptr->filename,ptr->count);
      	ptr = ptr->next;
   	}
	
   	printf("NULL\n");
}

int main()
{
	//insertFirst("ddd", "file2", 10);
	insertFirst("ccc", "file2", 9);
	insertFirst("ccc", "file3", 1);
	insertFirst("ccc", "file1", 1);
	insertFirst("ccc", "file3", 9);
	insertFirst("bbb", "file2", 4);
	insertFirst("bbb", "file3", 7);
	insertFirst("bbb", "file1", 1);
	insertFirst("bbb", "file3", 9);

	insertFirst("and", "file3", 20);
	insertFirst("and", "file2", 5);

	insertFirst("and", "file1", 3);



	
	insertFirst("aaa", "file1", 1);

	sort();

	printList(head);
	free(head);
	return 0;
}