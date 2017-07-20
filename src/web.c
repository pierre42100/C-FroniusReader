/**
 * Project web functions
 *
 * @author Pierre HUBERT
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */
#include <sys/socket.h> /* socket, connect */
#include <netinet/in.h> /* struct sockaddr_in, struct sockaddr */
#include <netdb.h> /* struct hostent, gethostbyname */

/**
 * Display an error
 */
void error(const char *msg) {
    perror(msg);
    exit(0);
}


/**
 * Perform a web request
 *
 * @param int limit The limit of the response to receive
 * @param const char *host Target host
 * @param int port Target port( 0 = default port)
 * @param const char *method The method to use for the request
 * @param const char *path The path of the request
 * @param const char *headers Headers to include with the request
 */
char* web_request(int limit, const char *host, int port, const char *method, const char *path, const char *headers){

    /* first where are we going to send it? */
    int portno = port > 0 ? port : 80;

    struct hostent *server;
    struct sockaddr_in serv_addr;
    int sockfd, bytes, sent, received, total, message_size;
    char *message;
    char *response;

    //Allocate memory for response
    response = malloc(limit * sizeof(char));

    //Check memory was allocated
    if(response == NULL){
        error("Couldn't allocate memory to store response !");
    }

    /* How big is the message? */
    message_size=0;
    if(!strcmp(method,"GET"))
    {
        message_size+=strlen("%s %s%s%s HTTP/1.0\r\n");        /* method         */
        message_size+=strlen(path);                         /* path           */
        message_size+=strlen("Host: \r\n");
        message_size+=strlen(host);
        message_size+=strlen(headers);                   /* headers        */
        message_size+=(strlen("\r\n"))*6;
        message_size+=strlen("\r\n");                          /* blank line     */
    }

    /* allocate space for the message */
    message=malloc(message_size);

    /* fill in the parameters */
    if(!strcmp(method,"GET"))
    {
        sprintf(message,"%s %s HTTP/1.0\r\n",
                method,               /* method         */
                path);                /* path           */

        //Add host
        strcat(message, "Host: ");
        strcat(message, host);
        strcat(message, "\r\n");

        strcat(message,"\r\n");                                /* blank line     */
    }


    /* What are we going to send? */
    //printf("Request:\n%s\n",message);

    /* create the socket */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) error("ERROR opening socket");

    /* lookup the ip address */
    server = gethostbyname(host);
    if (server == NULL) error("ERROR, no such host");

    /* fill in the structure */
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);

    /* connect the socket */
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    /* send the request */
    total = strlen(message);
    sent = 0;
    do {
        bytes = write(sockfd,message+sent,total-sent);
        if (bytes < 0)
            error("ERROR writing message to socket");
        if (bytes == 0)
            break;
        sent+=bytes;
    } while (sent < total);

    /* receive the response */
    //memset(response,0,sizeof(response));
    total = limit-1;
    received = 0;
    do {
        bytes = read(sockfd,response+received,total-received);
        if (bytes < 0)
            error("ERROR reading response from socket");
        if (bytes == 0)
            break;
        received+=bytes;

    } while (received < total);

    //Check if the response it too high
    if (received == total)
        fprintf(stderr, "Warning : response is too high to be completely stored! \n");

    /* close the socket */
    close(sockfd);

    //Free memory
    free(message);

    //Return response
    return response;
}

/**
 * Extract informations of a given URL
 *
 * @param const char *url The URL to retrieve the informations from
 * @param char **hostname The name of the host
 * @param char **address The address on the server
 * @return void
 */
void extract_url_informations(const char *url, char *hostname, char *address){

    int address_i = 0;
    int is_host_char = 1;
    int i;
    for(i = 0; url[i] != '\0'; i++){

        //Check if we have to switch from host part to address par
        if(url[i] == '/' && address_i == 0)
            is_host_char = 0;

        if(is_host_char == 1){
            hostname[i] = url[i];
            hostname[i+1]= '\0';
        }
        else {
            address[address_i] = url[i];
            address[address_i + 1] = '\0';

            address_i++;
        }

    }

    //End of function
    return;
}
