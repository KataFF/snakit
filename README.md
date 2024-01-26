# README of 
## Operating Systems and Exercises Final Project "SnakeIT"
### Project by Kajetan Wierszelis (カイェタン  ヴィエルシェリス) z523087
## What is this? Presentation.
Please see attached `OS-SnakeIT-Final-presentation-Demo-KxW-z523087` for a quick Presentation-form explanation.

## Where is the source code?
See `client.c` and `server.c`.

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

## Tools used.
The code was developed using `VS Codium` on `Manjaro Linux GNOME Edition`.
The Presentation was prepared using `Marp for VS Code` and `VS Codium`. [See website for Marp](https://marp.app/), Note, on Manjaro you need the `vscodium-bin-marketplace` AUR package to enable access to Microsoft's official Extension Marketplace.

I choose it since MS PowerPoint does not run on Linux (I mean, there's the in-browser version but last time I checked it was inferior to the desktop Windows one). Also writing content with code-defined formatting seems more productive than GUI editors (I used to use Google Slides before). Lastly, prefer open-source tools wherever possible, I believe they are worth investing time into and also can be forked when needed.
Raport was prepared using `Markdown Preview Enhance` extension for `VS Code`.

## Raport 
There's a raport `OS-SnakeIT_z523087_KajetanカイェタンWierszelisヴィエルシェリス_Final-Report` (both in Markdown and PDF form), see it too.
