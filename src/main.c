/**
 * Fronius reader
 *
 * A programm that read and parse the value of
 * power produced by a solar device (inverter)
 *
 * @author Pierre HUBERT
 */
#include <SDL2/SDL.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"
#include "web.h"
#include "fronius.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

#define PAUSE_DURATION 2

int main(int argc, char *argv[])
{
    //Welcome message
    fprintf(stdout, "Fronius inverters power reader.\n");
    fprintf(stdout, "(c) Pierre HUBERT 2017\n");
    fprintf(stdout, "Usage: fronius_reader [address_file]\n\n");

    //Define variables
    char *hostname, *address, *address_file;
    int produced_energy;

    //Check if a specific address file was specified
    if(argc < 2){
        address_file = "address.txt";
    }
    else {
        //Determine the right address file
        address_file = malloc(strlen(argv[1])*sizeof(char));
        strcpy(address_file, argv[1]);
    }

    //First, get the address to use to retrieve the value
    char *webAddress = get_file_contents(address_file, 200);

    //Inform user about the address to use
    fprintf(stdout, "Get live informations from: http://%s\n", webAddress);

    //Allocate both hostname and address with the same size as address
    hostname = malloc(strlen(webAddress)*sizeof(char));
    address = malloc(strlen(webAddress)*sizeof(char));

    //Check for allocation
    if(hostname == NULL || address == NULL){
        //This is a fatal error
        fprintf(stderr, "Couldn't allocate memory for hostname and / or address variables !\n");
        exit(EXIT_FAILURE);
    }

    //Extract informations from the URL
    extract_url_informations(webAddress, hostname, address);

    //Infinite loop
    while(1 == 1){
        //Perform the request on the server
        char *response = web_request(1000, hostname, 80, "GET", address, "");

        //Determine the produced amount of energy
        produced_energy = determine_inverter_produced_value(response);
        fprintf(stdout, "Currently, %d W are produced by the inverter.\n", produced_energy);

        //Free memory
        free(response);

        //Make a pause
        usleep(PAUSE_DURATION*1000000);
    }


    //Free memory
    free(hostname);
    free(address);

    //This is a success
    fprintf(stdout, "Exited cleany.\n");
    return EXIT_SUCCESS;
}
