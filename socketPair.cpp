#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>
#include <sys/socket.h>

int main(void)
{
    int sv[2]; /* the pair of socket descriptors */
    char buf[100]; /* for data exchange between processes */

    if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
        perror("socketpair");
        exit(1);
    }

    if (!fork()) {  /* child */
        read(sv[1], buf, 100);
        printf("child: read '%s'\n", buf);
        //buf = toupper(buf);  /* make it uppercase */
        write(sv[1], buf, 100);
        printf("child: sent '%s'\n", buf);

    } else { /* parent */
        write(sv[0], "bcd", 3);
        printf("parent: sent 'bcd'\n");
        read(sv[0], buf, 100);
        printf("parent: read '%s'\n", buf);
        wait(NULL); /* wait for child to die */
    }

    return 0;
}