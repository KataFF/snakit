/* z523087 - Final project SnakeIT client*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <ncurses.h> /* For non-line interactive terminal mode */
#include <time.h> /* timestamping */
#include <zlib.h> /* adler32 checksum */

/* Used knowledge sources:
	- System / C library programming manuals
	https://cboard.cprogramming.com/c-programming/157438-capturing-keyboard-input-one-character-time.html
	https://www.linuxquestions.org/questions/programming-9/detecting-arrow-key-presses-in-c-c-166055/
	https://opensource.com/article/21/8/ncurses-linux
 */

typedef struct {
    char input[BUFSIZ];
    time_t timestamp;
    unsigned long checksum;
} KeyboardInput;

typedef struct {
    int X;
    int Y;
    int score;
    int port;
} GameState;

int main(int argc, char *argv[]) {
    int sockfd, len;
    char buf[BUFSIZ];
    
    struct sockaddr_in serv;
    int port;
    if (argc != 3) {
        printf("Usage: ./client.elf host port\n");
        exit(1);
    }
    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }
    serv.sin_family = PF_INET;
    port = strtol(argv[2], NULL, 10);
    serv.sin_port = htons(port);
    inet_aton(argv[1], &serv.sin_addr);
    if (connect(sockfd,(struct sockaddr *)&serv, sizeof(serv)) < 0) {
        perror("connect");
        exit(1);
    }

    initscr();
    raw();
    noecho();
    nonl();
    keypad(stdscr, TRUE); /* Intercept arrow keys with flushing */

    KeyboardInput ki;
	GameState gs;
    char ch;

    srand(time(NULL));
    int randomPort = rand() % (65535 - 1024 + 1) + 1024;
    char portStr[6];
    sprintf(portStr, "%d", randomPort);
	move(4, 4);
	printw("Connected to server on port %d\n", randomPort);

    while ((ch = getch()) != 'Q') {
        ki.timestamp = time(NULL);
        strncpy(ki.input, &ch, 1);
		move(2, 4);
		printw("Pressed key code %d at time %d", &ch, ki.timestamp);
        ki.checksum = adler32(0, ki.input, strlen(ki.input));
        len = send(sockfd, (char*)&ki, sizeof(ki), 0);
        send(sockfd, portStr, strlen(portStr), 0);
        len = recv(sockfd, (char*)&gs, sizeof(ki), 0);
        ki.input[len] = '\0';
		move(8, 10);
        printw("Current position: (%d, %d), score %d, port %d\n", gs.X, gs.Y, gs.score, gs.port);
    }
    close(sockfd);
    endwin();
	return 0;
}