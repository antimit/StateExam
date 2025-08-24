#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();   // vytvoří nový proces

    if (pid < 0) {
        perror("fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child process
        printf("Child process, PID = %d, parent PID = %d\n", getpid(), getppid());
    }
    else {
        // Parent process
        printf("Parent process, PID = %d, child PID = %d\n", getpid(), pid);
    }

    return 0;
}
