/**
 * Project utilities
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

/**
 * Read & return the content of a file
 *
 * @param const char *filename The name of the file to read the content of
 * @param int limit The maximum size of the file to read
 * @return *char The read string
 */
char* get_file_contents(const char *filename, int limit){

    //Initialize target variable
    char *result;
    result = malloc(limit * sizeof(char));

    //Check the memory was allocated
    if(result == NULL){
        fprintf(stderr, "Couldn't allocate memory for target variable ! Need to exit now.\n");
        exit(EXIT_FAILURE);
    }

    //Open file
    int file = open(filename, 0);

    //Check for errors
    if(file == -1){
        fprintf(stderr, "Couldn't open file: %s!\n", filename);
        exit(EXIT_FAILURE);
    }

    //Read file
    read(file, result, limit);

    //Close file
    close(file);

    //Return result
    return result;
}
