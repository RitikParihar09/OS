#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAX_TEXT 100

struct message {
    long msg_type;
    char text[MAX_TEXT];
};

int main() {
    int msgid;
    struct message msg;
    pid_t pid;

    // Create a message queue
    msgid = msgget(IPC_PRIVATE, 0666 | IPC_CREAT);
    if (msgid == -1) {
        printf("error");
    }

    // Create a child process
    pid = fork();
    if (pid < 0) {
        printf("error creating child process");
    }

    if (pid == 0) {  // Child process
        msg.msg_type = 1;
        strcpy(msg.text, "Message from Child.");
        msgsnd(msgid, &msg, sizeof(msg.text), 0);
        exit(0);
    } else {  // Parent process
        msgrcv(msgid, &msg, sizeof(msg.text), 1, 0);
        printf("Parent received: %s\n", msg.text);

        // Remove message queue
        msgctl(msgid, IPC_RMID, NULL);
    }

    return 0;
}
