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

#endif // UTILS_H_INCLUDED
