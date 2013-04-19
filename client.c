#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int client (char *host, int port, char *filename);

int main (int argc, char *argv[])
{
char *host, *filename;
int port, r;

assert (argc == 4);
host = argv[1];
port = atoi (argv[2]);
filename = argv[3];

r = client (host, port, filename);
return r;
}

int client (char *host, int port, char *filename)
{
int r, s;
struct sockaddr_in sin;
char buf[1024];

/* Setup the socket */
s = socket (AF_INET, SOCK_STREAM, 0);

/* Make the connection */
/* The function bzero() sets the first n bytes of the area starting at s to zero */
bzero (&sin, sizeof (sin));
sin.sin_family = AF_INET;
sin.sin_port = htons (port);
/* inet_aton() converts the Internet host address cp from the IPv4 numbers-and-dots notation 
into binary form (in network byte order) and stores it in the structure that inp points to. 
inet_aton() returns nonzero if the address is valid, zero if not. 
The address supplied in cp can have one of the following forms:
*/
inet_aton (host, &sin.sin_addr);


connect (s, (struct sockaddr *) &sin, sizeof (sin));
puts("Yippee!");
/* Write the filename */
write (s, filename, strlen (filename));
write (s, "\n", 1);

/* Send the bytes that come back to stdout */
while ((r = read (s, buf, sizeof (buf))) > 0){
	write (1, buf, r);
}

/* Finish out */
close (s);
return 0;
}
