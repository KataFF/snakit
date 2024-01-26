# README of 
## Operating Systems and Exercises Final Project "SnakeIT"
### Project by Kajetan Wierszelis (カイェタン  ヴィエルシェリス) z523087
## What is this?
Please see attached `OS-SnakeIT-Final-presentation-Demo-KxW-z523087` for a quick Presentation-form explanation.

## Running/compiling general instructions:
For testing each part you can use the `run` script as usual, which compiles and runs the program (if executable is created):
```sh
./run <programm-name without .c> <program arguments>
```
## How to automatically compile and run (Usage instructions)
It's almost fully automated - see `Makefile`. How to: 
- Run `make`. 
- Select any client window
- Press some key.
- Observe received position change.
- Repeat from "press some key" step.

To run it as is, `localhost` has to be set in `/etc/hosts` (it is by default on most Linux distros). Otherwise replace `localhost` with your PC's IP address to send the packets thru LAN. If needed, you can alter the variables inside the `Makefile` like the address, port to allow e.g. for running server and client on separate machines (by default it runs on the same PC).
