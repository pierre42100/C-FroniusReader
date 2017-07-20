#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

/**
 * Project web functions - Header file
 *
 * @author Pierre HUBERT
 */

/**
 * Perform a web request
 *
 * @param int limit The limit of the response to receive
 * @param const char *host Target host
 * @param int port Target port( 0 = default port)
 * @param const char *method The method to use for the request
 * @param const char *path The path of the request
 * @param const char *headers Headers to include with the request
 * @return const char *response The request response
 */
char* web_request(int limit, char *host, int port, const char *method, const char *path, const char *headers);


/**
 * Extract informations of a given URL
 *
 * @param const char *url The URL to retrieve the informations from
 * @param char **hostname The name of the host
 * @param char **address The address on the server
 * @return void
 */
void extract_url_informations(const char *url, char *hostname, char *address);

#endif // WEB_H_INCLUDED
