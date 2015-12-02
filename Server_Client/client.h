#ifndef __CLIENT_H__
#define __CLIENT_H__

#define net_assert(err, errmsg) { if ((err)) { perror(errmsg); assert(!(err)); } }

#define QUERY_MAXLENGTH 400
#define RESPONSE_MAXLENGTH 400
#define CLIENT_MAXFNAME    256  // including terminating NULL
#define CLIENT_PORTSEP     ':'
#define CLIENT_QLEN       10 

extern int sd;

#endif /* __CLIENT_H__ */
