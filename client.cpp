#include <stdio.h>         // fprintf(), perror(), fflush()
#include <stdlib.h>        // atoi()
#include <assert.h>        // assert()
#include <string.h>        // memset(), memcmp(), strlen(), strcpy(), memcpy()
#include <unistd.h>        // getopt(), STDIN_FILENO, gethostname()
#include <netdb.h>         // gethostbyname()
#include <netinet/in.h>    // struct in_addr
#include <arpa/inet.h>     // htons()
#include <sys/types.h>     // u_short
#include <sys/socket.h>    // socket API
#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctime>
#include "client.h"

int sd;                   /* socket descriptor */

void client_usage(char *progname)
{
  fprintf(stderr, "Usage: %s -s <server>:<port> -q <query>\n",
          progname); 
  exit(1);
}

/*
 * client_args: parses command line args.
 * "*sname"     : the server's name
 * "port"       : the port to connect at server, in network byte order. 
 * "*imagename" : the name of the image to search for
 * "*vers"      : the version used for query packet
 */
int client_args(int argc, char *argv[], char **sname, u_short *port, char *query)
{
  char c, *p;
  extern char *optarg;

  if (argc < 5) {
    return (1);
  }
  
  while ((c = getopt(argc, argv, "s:q:")) != EOF) {
    switch (c) {
    case 's':
      for (p = optarg+strlen(optarg)-1;      // point to last character of addr:port arg
           p != optarg && *p != CLIENT_PORTSEP;  // search for ':' separating addr from port
           p--);
      net_assert((p == optarg), "client_args: server address malformed");
      *p++ = '\0';
      *port = htons((u_short) atoi(p)); // always stored in network byte order
      *sname = optarg;
      break;
    case 'q':
      memcpy(query, optarg, strlen(optarg));
      break;
    default:
      return(1);
      break;
    }
  }

  return (0);
}

/*
 * client_sockinit: creates a new socket to connect to the provided server.
 * The server's FQDN and port number are provided.  The port number
 * provided is assumed to already be in netowrk byte order.
 *
 * On success, the global socket descriptor sd is initialized.
 * On error, terminates process.
 */
void client_sockinit(char *sname, u_short port)
{
  /* 
   * create a new TCP socket, store the socket in the global variable sd
   */
  if ((sd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    abort();

  /* 
   * obtain the server's IPv4 address from sname and initialize the
   *  socket address with server's address and port number . 
   */
  struct sockaddr_in sin;
  struct hostent *host = gethostbyname(sname);
  memset(&sin, 0, sizeof(sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = *(unsigned long *)host->h_addr_list[0];
  sin.sin_port = port;

  /* connect to server */
  if (connect(sd, (struct sockaddr *) &sin, sizeof(sin)) < 0)
    abort();

  return;
}

/*
 * client_sendquery: send query to server
 */
int client_sendquery(char *query)
{
  int bytes;
  bytes = send(sd, query, QUERY_MAXLENGTH, 0);
  if (bytes != QUERY_MAXLENGTH) {
    return(0);
  }
  return(1);
}

/*
 * client_sendquery: send termination message to server
 */
void client_sendtermination()
{
  if (send(sd, "terminate", QUERY_MAXLENGTH, 0) < 0)
    abort();

}

/*
 * client_recvresponse: receive response from server
 */
int client_recvresponse(char* response)
{
  if (recv(sd, response, RESPONSE_MAXLENGTH, 0) <= 0) 
    return 0;
  else return 1;
}

int main(int argc, char *argv[])
{
  int err;
  char *server_name;
  u_short port;
  clock_t startTime;
  clock_t endTime;
  char query[QUERY_MAXLENGTH] = { 0 };
  char response[RESPONSE_MAXLENGTH] = { 0 };

  /* parse args */
  if (client_args(argc, argv, &server_name, &port, query)) {
    client_usage(argv[0]);
  }

  client_sockinit(server_name, port); 

  std::ifstream input_file("sql/search_test_int.sql");
  if (input_file.is_open()) {

    /* set the start time */
    startTime = clock();

    /*
     * read queries from input file line by line
     * send each query to server and wait for the response
     */
    while (!input_file.eof()) {
      input_file.getline(query, QUERY_MAXLENGTH);
      fprintf(stderr, "query = %s\n", query);
      if (client_sendquery(query)) {
        if (client_recvresponse(response) == 1) {
          fprintf(stderr, "query found: response = %s\n", response);
        } else {
          fprintf(stderr, "query not found.\n");
        } 
      }
      else {
        fprintf(stderr, "error in sending query.\n");
      }
    }

    /* set the end time */
    endTime = clock();

    /* send the termination to server to close the connection */
    client_sendtermination();
  }

  fprintf(stderr, "time = %f\n", ((double)(endTime - startTime))/CLOCKS_PER_SEC);

  
  
  return(0);
}
