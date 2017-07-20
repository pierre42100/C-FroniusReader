#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

/**
 * Project utilites - header file
 *
 * @author Pierre HUBERT
 */

/**
 * Read & return the content of a file
 *
 * @param const char *filename The name of the file to read the content of
 * @param int limit The maximum size of the file to read
 * @return *char The read string
 */
char* get_file_contents(const char *filename, int limit);

/**
 * Generates a random number in a specified interval
 *
 * @param int min The minimum number
 * @param int max The maximum number
 * @return int The result number
 */
int alea(int max, int min);

/**
 * Generate & display a fatal error
 *
 * @param const char *error_msg The error message
 * @return void (The function quit the programm)
 */
void fatal_error(const char *error_msg);

#endif // UTILS_H_INCLUDED
