# YEAST

![logo](src/yeast.ico)

**YE**t
**A**nother
**S**imple
**T**imetracker

> [!WARNING]
> WIP. Some features are still missing. It seems kind of stable, but backup your notes before use it.

## Introduction

The project started on March 2023 for educational purpose. I changed the GUI and re-designed many times, just because I didn't spent enough time to understand my (the user) needs and the daily workflow.  
I'll probably do some code refactoring, abstracting class here and there ... but at least the scope is now clear.

This is not elegant, well written C++, if you are looking for that, then this is not the right project.

### The goal

> Always keep track of time spent on tasks. One day the management will come to you asking for numbers, and reasons ... be prepared!

The goal of *YE.A.S.T.* is to measure the time spent on daily task and provide a simple interface to track them.  
Last three years I just used a plain text file to solve perfectly this scope, *"Live simply"*. But I have admit that when your list start to be bigger a kind of highlighting syntax and few quick automation can make your life easier at standup meetings (or when managers call you asking the progress status).

Each operation shall be done via keyboard input (do not waste time using the mouse).

### Features

+ Based on regular text file
+ Tasks and sub-task can be written freely together with notes
+ Sub-tasks can have a STATUS highlighted in different colors for quick eye-scan-overview
+ Minutes/hours spent on tasks must be *automatically* tracked and written in the same text file
+ Prefer key shortcuts instead of mouse (no button, no right-click menù ...)
+ Stripped-back GUI

## User Manual

There is a kind of portable beta release here:

| File | Architecture | Checksum MD5 |
| --- | --- | --- |
| [YEAST_v_0_6_BETA_Win64bit_portable.7z](releases/YEAST_v_0_6_BETA_Win64bit_portable.7z) | MS Windows 11 x64 | fc8acf9255a2271ceeca6456b900135e |

But I highly suggest to clone the project and run it via Qt creator IDE (Qt 5.15.x).

The editor open the local file "", and basically is just a text editor with some pre-defined syntax highlighting.

I put some notes directly on that file, to explain how things work on the fly... After that you can entirely rewrite the content according to your needs and workflow.

### Key shortcuts

+ *CTRL + h* : show help
+ *CTRL + l* : enable/disable auto screen lock (see NOTE-1)
+ *CTRL + t* : toggle sub-tasks status (todo, progress, wait, done)
+ *CTRL + r* : start/stop task time recording
+ *CTRL + s* : save text (see NOTE-2)

## Software architecture

TODO

## F.A.Q.

**NOTE-1**  
some company laptop have automatic lock protection that switch to login screen when there no user interaction for x minutes.  
Frankly this *feature* is quite annoying when you are staring at some design document writing notes on paper or just trying to understand the issue and a #@*! wallpaper with login appears on screen.
To avoid that I added a simple workaround using OS signals, nothing fancy, make you research on the web :)  
*Anyway privacy and safety are important for companies, I understand their requirements, just don't make my job more difficult!*

**NOTE-2**  
There is also an autosave timer running in background every 5 minutes, and finally it saves also before exiting the program.

## Contribute

No guidelines right now.  
For tips, problems, comments just open an issue and we'll think about it... Thanks!

## License

The *YE.A.S.T.* software is licensed under the [GNU General Public License Version 3](http://www.gnu.org/licenses/gpl.html). 
Please refer to LICENSE file for details.
