#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <syslog.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // Open syslog with LOG_USER facility and include PID
    openlog("writer", LOG_PID, LOG_USER);

    // Validate argument count (argv[0]=program, argv[1]=file path, argv[2]=write string)
    if (argc != 3) {
        syslog(LOG_ERR, "Error: Invalid number of arguments. Expected 2, got %d", argc - 1);
        fprintf(stderr, "Usage: %s <writefile> <writestr>\n", argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    // Log the write operation at LOG_DEBUG level as required by the assignment
    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    // Open file for writing; create if missing; truncate if it exists; permissions 0664
    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    if (fd == -1) {
        syslog(LOG_ERR, "Error opening/creating file %s: %s", writefile, strerror(errno));
        perror("open failed");
        closelog();
        return 1;
    }

    // Write the contents of writestr to the file
    size_t len = strlen(writestr);
    ssize_t bytes_written = write(fd, writestr, len);
    if (bytes_written == -1 || (size_t)bytes_written != len) {
        syslog(LOG_ERR, "Error writing to file %s: %s", writefile, strerror(errno));
        perror("write failed");
        close(fd);
        closelog();
        return 1;
    }

    // Close the file descriptor
    if (close(fd) == -1) {
        syslog(LOG_ERR, "Error closing file %s: %s", writefile, strerror(errno));
        perror("close failed");
        closelog();
        return 1;
    }

    closelog();
    return 0;
}

