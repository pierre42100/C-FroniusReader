#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

/**
 * Window functions - header file
 *
 * @author Pierre HUBERT
 */
#include <SDL2/SDL.h>

/**
 * Initializate SDL & create renderer & create window
 *
 * @param int w
 * @param in h > Window dimensions
 * @return void (Programm quit if it fails)
 */
void initilizate_ui(int w, int h);

/**
 * Load graphical numbers
 *
 * Load numbers that will be used for the UI
 *
 * @param const char *filename The name of the images file
 * @return void (Fatal error if it fails)
 */
void load_graphical_numbers(const char *filename);

/**
 * Fill the renderer with one color
 *
 * @param SDL_Color color The color to use to fill the renderer
 */
void fill_renderer(SDL_Color color);

/**
 * Update the window with a given number
 *
 * @param int number The new number to display on the screen (-1 = empty screen)
 * @return void
 */
void update_screen(int number);

/**
 * Quit SDL :
 * - Destroy textures
 * - Destroy renderer
 * - Destroy window
 * - Quit SDl
 */
void quit_sdl();

#endif // WINDOW_H_INCLUDED
