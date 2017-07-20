/**
 * Window functions
 *
 * @author Pierre HUBERT
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "window.h"

/**
 * Variables definition
 */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
static SDL_Texture *numbers_texture = NULL;

/**
 * A few colors definition...
 */
SDL_Color black = {0, 0, 0, 255};

/**
 * Initializate SDL & create renderer & create window
 *
 * @param int w
 * @param in h > Window dimensions
 * @return void (Programm quit if it fails)
 */
void initilizate_ui(int w, int h){

    //Initializate SDL
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fatal_error("Couldn't initializate SDL Library !");
    }

    //Create Windows
    window = SDL_CreateWindow("Fronius Reader", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN);

    //Check for errors
    if(window == NULL){
        fatal_error("Couldn't create SDL Windows !");
    }

    //Create renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    //Check if we have to fall back to render software
    if(renderer == NULL){
        //Display error
        fprintf(stderr, "Couldn't use accelerated renderer, falling back to software renderer. (Err: %s)\n", SDL_GetError());
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    }

    //Check for errors
    if(renderer == NULL){
        //This is a fatal error
        fatal_error("Couldn't initilizate renderer (tryed both software & accelerated renderer !");
    }

    //Fill renderer
    fill_renderer(black);

    //End of function
    return;

}

/**
 * Load graphical numbers
 *
 * Load numbers that will be used for the UI
 *
 * @param const char *filename The name of the images file
 * @return void (Fatal error if it fails)
 */
void load_graphical_numbers(const char *filename){

    //Try to load numbers
    SDL_Surface *surface_numbers = IMG_Load(filename);

    //Check for errors
    if(surface_numbers == NULL){
        //This is a fatal error
        fatal_error("Couldn't load numbers image! Exiting...");
    }

    //Convert surface numbers into a texture
    numbers_texture = SDL_CreateTextureFromSurface(renderer, surface_numbers);

    if(numbers_texture == NULL){
        fatal_error("Couldn't convert numbers surface into texture !");
    }

    //Free memory
    SDL_FreeSurface(surface_numbers);

    //End of function
    return;
}


/**
 * Fill the renderer with one color
 *
 * @param SDL_Color color The color to use to fill the renderer
 */
void fill_renderer(SDL_Color color){
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    //End of function
    return;
}

/**
 * Update the window with a given number
 *
 * @param int number The new number to display on the screen (-1 = empty screen)
 * @return void
 */
void update_screen(int number){
    //Information message
    fprintf(stdout, "Update screen with the following new value: %d\n", number);

    //Empty screen
    SDL_SetRenderTarget(renderer, NULL);
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    SDL_RenderClear(renderer);

    //Check if we just have to empty screen
    if(number == -1){
        fill_renderer(black);
        return; //Nothing to be done more
    }

    //Convert the integer into a string
    char numbers[10];
    sprintf(numbers, "%d", number);

    int pos = 0 ;;
    //Display each number
    for(int i = 0; numbers[i] != '\0'; i++){

        //Determine destination
        SDL_Rect dest = {pos*26, 0, 26, 50};

        //Determine source
        SDL_Rect src = {(numbers[i] - '0')*27, 0, 26, 50};

        //Apply new value
        SDL_RenderCopy(renderer, numbers_texture, &src, &dest);

        //Update position
        pos++;
    }

    //Update renderer
    SDL_RenderPresent(renderer);

    //End of function
    return;
}
