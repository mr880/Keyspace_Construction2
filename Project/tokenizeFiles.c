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
#include "pointersorter.c"


int is_regular_file(const char *path);
static unsigned get_file_size (const char * file_name);
void tokenize_file(char* directory, char* filename);

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1) + strlen(s2) + 1); // +1 for the null-terminator
    // in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

static unsigned get_file_size (const char * file_name)
{
    struct stat sb;
    if (stat (file_name, & sb) != 0) {
        fprintf (stderr, "'stat' failed for '%s': %s.\n", file_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    return sb.st_size;
}

void listdir(char *name, int indent)
{
    DIR *dir;
    struct dirent *entry;
    

    if (!(dir = opendir(name)))
        return;

    //printf("Name: %s\n", name);


    while ((entry = readdir(dir)) != NULL) {
    	
        if (entry->d_type == DT_DIR) {
            char path[1024];
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            printf("%*s[%s]\n", indent, "", entry->d_name);

            listdir(path, indent + 2);

        } else {
        	
        	//char** abc = tokenize_file(entry->d_name);

            printf("%*s- %s\n", indent, "", entry->d_name);

           	tokenize_file(name, entry->d_name);

        }
    }
    closedir(dir);
}

void tokenize_file(char* directory, char* filename)
{
	int fd;
	int c; 
	char *result = malloc(strlen(directory) + strlen(filename) + 1);
	strcpy(result, directory);
	strcat(result, "/");
    strcat(result, filename);
	

	unsigned size = get_file_size(result);

	char data[size];
	printf("----------------------------\n");
	printf("File: %s\n", result);
	fd = open(result, O_RDWR, 0);

	ssize_t reader = read(fd, data, size);
	printf("Data: %s\n", data);

	char* delimterInput = insertDelimeterReturnsString(data);

	numTokens = returnNumTokens(delimterInput);

	char** tokenArray = inputStringReturnsTokenArray(delimterInput, numTokens);

	tokenArrayReturnsAlphaArray(tokenArray, filename);

	printf("----------------------------\n");

	c = close(fd);
	// free(tokenArray);
	// free(delimterInput);
	free(result);
	return;
}

int main(int argc, char** argv)
{

	if(argc > 3)
	{
		printf("Too many arguments!\n");
		return 0;
	}

	char* file = argv[1];
	
	

	listdir(file, 2);
	
	sort();
	countsort();
	printList(head);


    writefile();

	
	free(head);
	return 0;

}
