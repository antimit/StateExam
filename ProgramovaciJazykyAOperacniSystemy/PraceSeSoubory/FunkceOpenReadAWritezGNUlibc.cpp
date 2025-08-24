#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main() {
    int fd = open("test.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    const char *msg = "Hello, world!\n";
    if (write(fd, msg, strlen(msg)) == -1) {
        perror("write");
    }
    close(fd);

    fd = open("test.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    char buf[128];
    ssize_t bytes = read(fd, buf, sizeof(buf)-1);
    if (bytes == -1) {
        perror("read");
    } else {
        buf[bytes] = '\0';
        printf("Read: %s", buf);
    }
    close(fd);

    return 0;
}
