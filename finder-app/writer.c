#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>


int main(int argc, char ** argv) {
    openlog("writer", LOG_CONS, LOG_USER);

    if (argc != 3) {
        printf("usage: writer writefile writestr\n");
        syslog(LOG_ERR, "wrong invocation");
        return 1;       
    }

    char *fnm = argv[1];
    char *txt = argv[2];

    int fd = open(fnm, O_CREAT | O_TRUNC | O_WRONLY, 0644);

    if (fd < 0) {
        syslog(LOG_ERR, "error opening file %s error=%s", fnm, strerror(errno));
        return 1;
    }
    syslog(LOG_DEBUG, "opened file=%s fd=%d", fnm, fd);

    int i = 0;
    int n = strlen(txt);
    int err = 0;
    while (i < n) {
        int written = write(fd, txt + i, n - i);
        if (written < 0) {
            err = errno;
            syslog(LOG_ERR, "error writing error=%s", strerror(err));
            break;
        }
        i += written;
    }

    close(fd);

    closelog();

    return 0;
}