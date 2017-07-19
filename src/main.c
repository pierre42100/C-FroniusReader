/**
 * Fronius reader
 *
 * A programm that read and parse the value of
 * power produced by a solar device
 *
 * @author Pierre HUBERT
 */
#include <SDL2/SDL.h>

#include "utils.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, char *argv[])
{
    //First, get the address to use to retrieve the value
    char *webAddress = get_file_contents("address.txt", 200);

    //Inform user about the address to use
    fprintf(stdout, "Get live informations from: %s\n", webAddress);

    //This is a success
    fprintf(stdout, "Exited cleany.\n");
    return EXIT_SUCCESS;
}
