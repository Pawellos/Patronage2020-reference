#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>

#define MAXBUF 4096

int main(void)
{
    int sd, c;
    struct sockaddr_in sa;
    socklen_t sl;

    memset(&sa, 0, sizeof(sa));
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.s_addr = INADDR_ANY;
    sl = sizeof(sa);

    if ((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return 1;

    if (bind(sd, (struct sockaddr *) &sa, sl) < 0)
        return 1;

    if (listen(sd, 5) < 0)
        return 1;

    while((c = accept(sd, (struct sockaddr *) &sa, &sl)) >= 0) {
        char buf[MAXBUF], needle[MAXBUF], haystack[MAXBUF], *ptr;
        ssize_t len;

        len = read(c, buf, sizeof(buf) - 1);
        buf[len] = '\0';

        if (sscanf(buf, "%s%s", needle, haystack) == 2) {
            ptr = strstr(haystack, needle);
            sprintf(buf, "%ld", ptr ? ptr - haystack : -1L);
            write(c, buf, strlen(buf));
        }

        close(c);
    }

    return 0;
}
