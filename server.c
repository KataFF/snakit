/* z523087 - Final project SnakeIT server, based on Class 9 socket server */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stddef.h> /* size_t */
#include <ncurses.h> /* for KeyboardInput structure contents */

typedef struct {
    int key;
    time_t timestamp;
    unsigned long checksum;
} KeyboardInput;

typedef struct {
    int X;
    int Y;
    int score;
    uint16_t port;
} GameState;

int main(int argc, char *argv[]) {
    int sockfd, len, new_sockfd, pipefd[2];
    char buf[BUFSIZ];
    struct sockaddr_in serv, clnt;
    socklen_t sin_siz;
    int port;
    if (argc != 3) {
        printf("Usage: ./server.elf host port\n");
        exit(1);
    }
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    printf("socket() called\n");
    serv.sin_family = PF_INET;
    port = strtol(argv[2], NULL, 10);
    serv.sin_port = htons(port);
    inet_aton(argv[1], &serv.sin_addr);
    sin_siz = sizeof(struct sockaddr_in);
    if (bind(sockfd, (struct sockaddr * ) &serv, sizeof(serv)) < 0) {
        perror("bind");
        exit(1);
    }
    printf("bind() called\n");
    if (listen(sockfd, SOMAXCONN) < 0) {
        perror("listen");
        exit(1);
    }
    printf("listen() called\n");
    
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_sockfd = accept(sockfd, (struct sockaddr *) &clnt, &sin_siz)) < 0) {
            perror("accept");
        }
        printf("connect from %s: %d\n", inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));
        memset(buf, 0, BUFSIZ);

        pid_t pid = fork();
        if (pid < 0) {
            perror("fork failed");
            exit(1);
        } else if (pid == 0) {
            close(sockfd);
            close(pipefd[0]); /* Close read end of pipe in child */
			
            bool keepRunning = true;
			KeyboardInput ki;
            GameState gs;
            gs.X = 0;
            gs.Y = 0;
            gs.score = 0;
            gs.port = ntohs(clnt.sin_port); /* Add player's port to GameState */

            while ((recv(new_sockfd, (char*)&ki, sizeof(ki), 0) > 0 ) && keepRunning) { /* Receive KeyboardInput from client */
				switch (ki.key) {
					case KEY_UP:
						gs.Y--;
						break;
					case KEY_DOWN:
						gs.Y++;
						break;
					case KEY_LEFT:
						gs.X--;
						break;
					case KEY_RIGHT:
						gs.X++;
						break;
                    case 'q':    
					case 'Q':
						keepRunning = false; /* Would be simpler to "goto" outside of this while loop, but less elegant. */
						break;
				}
                write(pipefd[1], (char*)&gs, sizeof(gs)); /* Write game state to pipe */
				len = send(sockfd, (char*)&gs, sizeof(gs), 0); /* Send game state to client */
            }
            printf("client/player on port %s disconnected.", gs.port);
            close(pipefd[1]); /* Close write end of pipe in child */
			close(new_sockfd); /* Added post-demo - I forgot this, overwrote when adding pipe capabilites*/
            exit(0);
        } else {
            continue;
        }
    }

    close(sockfd);
    close(pipefd[1]); /* Close write end of pipe in parent */

    GameState gs;
    while (read(pipefd[0], (char*)&gs, sizeof(gs)) > 0) {
        printf("Player position: (%d, %d) Port: %d\n", gs.X, gs.Y, gs.port);
    }

    close(pipefd[0]); /* Close read end of pipe in parent */
    return 0;
}

