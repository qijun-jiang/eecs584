#include <stdio.h>         // fprintf(), perror(), fflush()
#include <stdlib.h>        // atoi()
#include <assert.h>        // assert()
#include <iostream>
#include <string.h>        // memset(), memcmp(), strlen(), strcpy(), memcpy()
#include <unistd.h>        // getopt(), STDIN_FILENO, gethostname()
#include <netdb.h>         // gethostbyname(), gethostbyaddr()
#include <netinet/in.h>    // struct in_addr
#include <arpa/inet.h>     // htons(), inet_ntoa()
#include <sys/types.h>     // u_short
#include <sys/socket.h>    // socket API, setsockopt(), getsockname()
#include "client.h"

/*
 * server_sockinit: sets up a TCP socket listening for connection.
 * Let the call to bind() assign an ephemeral port to this listening socket.
 * Determine and print out the assigned port number to screen so that user
 * would know which port to use to connect to this server.
 *
 * Terminates process on error.
 * Returns the bound socket id.
 */
int
server_sockinit()
{
  int sd;
  struct sockaddr_in self;
  char sname[CLIENT_MAXFNAME+1] = { 0 };

  /* create a TCP socket, store the socket descriptor in global variable "sd" */
  if ((sd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) 
    abort();

  memset((char *) &self, 0, sizeof(struct sockaddr_in));
  self.sin_family = AF_INET;
  self.sin_addr.s_addr = INADDR_ANY;
  self.sin_port = 0;

  /* bind address to socket */
  if (bind(sd, (struct sockaddr *) &self, sizeof(struct sockaddr_in)) < 0) 
    abort();

  /* listen on socket */
  if (listen(sd, CLIENT_QLEN)  < 0) 
    abort();

  /* Obtain the ephemeral port assigned by the OS kernel to this
   * socket and store it in the local variable "self".
   */
  unsigned addr_len = sizeof(self);
  if (getsockname(sd, (sockaddr *)&self, &addr_len) < 0)
    abort();

  /* Find out the FQDN of the current host and store it in the local
     variable "sname".  gethostname() is usually sufficient. */
  if (gethostname(sname, CLIENT_MAXFNAME+1) < 0) 
    abort();

  /* inform user which port this peer is listening on */
  fprintf(stderr, "server address is %s:%d\n", sname, ntohs(self.sin_port));

  return sd;
}

/*
 * server_accept: accepts connection on the given socket, sd.
 * Terminates process on error.
 */
int
server_accept(int sd)
{
  int td;
  struct sockaddr_in client;
  struct hostent *cp;

  /* Accept the new connection.
   * Use the variable "td" to hold the new connected socket.
   */
  unsigned addr_len = sizeof(client);
  if ((td = accept(sd, (struct sockaddr *) &client, &addr_len)) < 0)
    abort();

  /* inform user of connection */
  cp = gethostbyaddr((char *) &client.sin_addr, sizeof(struct in_addr), AF_INET);
  fprintf(stderr, "Connected from client %s:%d\n",
          ((cp && cp->h_name) ? cp->h_name : inet_ntoa(client.sin_addr)),
          ntohs(client.sin_port));

  return td;
}

/* 
 * server_recvquery: receive query from td 
 */
void
server_recvquery(int td, char *query)
{
  if (recv(td, query, QUERY_MAXLENGTH, 0) < 0)
    abort();
  return;
}

/* 
 * server_sendresponse: send response through td 
 */
void
server_sendresponse(int td, char *response)
{
  if (send(td, response, RESPONSE_MAXLENGTH, 0) < 0)
    abort();
  return;
}

int
main(int argc, char *argv[])
{ 
  int sd, td;
  char query[QUERY_MAXLENGTH] = { 0 };
  char response[RESPONSE_MAXLENGTH] = "response\0";
  char termination[RESPONSE_MAXLENGTH] = "terminate\0";

  sd = server_sockinit();
  
  while (1) {
    /* connect with a client */
    td = server_accept(sd); 

    /* receive queries and response answers to the client */
    while (1) {
      server_recvquery(td, query); 
      fprintf(stderr, "%s\n", query);

      /* check termination */
      if (strcmp(query, "terminate") == 0) {
        server_sendresponse(td, termination);
        close(td);
        break;
      }

      /* if it is not terminated */
      // process the query 
      // execute(query);

      // send response to the client
      server_sendresponse(td, response);
    }
  }

  exit(0);
}