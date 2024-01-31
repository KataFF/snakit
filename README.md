# README of 
## Operating Systems and Exercises Final Project "SnakeIT"
### Project by Kajetan Wierszelis (カイェタン  ヴィエルシェリス) z523087
## What is this? Presentation.
Please see attached `OS-SnakeIT-Final-presentation-Demo-KxW-z523087` for a quick Presentation-form explanation. It's been virtually unaltered from the in-class presented form.

### Raport 
There's also a raport `OS-SnakeIT_z523087_KajetanカイェタンWierszelisヴィエルシェリス_Final-Report` (both in Markdown and PDF form), see it too.

## Where is the source code?
See `client.c` and `server.c`. General alghoritm of program is explained in Raport mentioned above to keep this README short.

## How to automatically compile and run demo
It's almost fully automated - see `Makefile`. How to: 
- Run `make`. 
- Select any client window
- Press any arrow key.
- Observe received position change.
- Repeat from "press some key" step, or...
- Press q or Shift+Q in client to exit main program loop and close the connection to server.
- Server will terminate if all connections are closed. 

To run it as is, `localhost` has to be set in `/etc/hosts` (it is by default on most Linux distros). Otherwise replace `localhost` with your PC's IP address to send the packets thru LAN. If needed, you can alter the variables inside the `Makefile` like the address, port to allow e.g. for running server and client on separate machines (by default it runs on the same PC).

## Individual component running/compiling general instructions:
For testing each part you can use the `run` script as usual, which compiles and runs the program (if executable is created):
```sh
./run <server or client, without .c> <IP address (try localhost first)> <IP port> 
```
