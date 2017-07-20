/**
 * Project utilities
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

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

/**
 * Generates a random number in a specified interval
 *
 * @param int min The minimum number
 * @param int max The maximum number
 * @return int The result number
 */
int alea(int max, int min){
    srand(time(NULL));
    return (rand() % (max - min + 1)) + min;
}

/**
 * Generate & display a fatal error
 *
 * @param const char *error_msg The error message
 * @return void (The function quit the programm)
 */
void fatal_error(const char *error_msg){
    fprintf(stderr, "A fatal error occured: %s\n", error_msg);
    fprintf(stderr, "SDL2.0_Error: %s\n", SDL_GetError());
    exit(EXIT_FAILURE);
}
