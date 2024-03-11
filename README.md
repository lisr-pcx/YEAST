# YEAST

**YE**t
**A**nother
**S**imple
**T**imetracker

> [!WARNING]
> Missing feature, source code is not stable, CSS stylesheet are really ugly ... work in progress

## Introduction

The project started on March 2023 for educational purpose.

> [!TIP]
> Always keep track of time spent on tasks, the management will come asking for numbers (and they are not friendly)

## Description

The goal of *YE.A.S.T.* is to measure the time spent on daily task and provide a simple easy interface. 

Each operation shall be done via keyboard input (do not waste time using the mouse).

**Keyboard commands**

* <CTRL> + <i> : show information box
* <CTRL> + <h> : show records history
* <CTRL> + <UP> : when history is available, then search records on previous date
* <CTRL> + <DOWN> : when history is available, then search records on next date
* <CTRL> + <L> : enable or disable the lock of the screen
* <CTRL> + <0> .. <9> : toggle monitoring on the specific task

## IDE and toolchain

Please use Qt creator 5.15.x.

## Overview

### Class Dashboard

This is the main window for the user (GUI).

* Load and enable screen unlock
* Manage key press
* Load time tracker manager
* Load history widget

### Class DbManager

On the first draft of this application have been used CSV files, but currently as SQL lite database is used to store all records. 
The database is created if it does not exist (YEAST.db)

Design pattern: Singleton

### Class History

Widget for records navigation. 
Currently is not implemented a model-view pattern, data are just retrieved from database and showed.

### Class ScreenUnlock

When enabled send periodically signals to OS, to keep process active and avoid automatic screen lock features from administrators.

### Class SingleRecord

This class represent a single record (allocated into dynamic memory). 
A dedicated Timer object is used in order for time monitoring (it counts minutes).

### Class Timetracker

This class do all business logic about record creation and store.
An ended record is instantly stored into databse. 
At application startup all records of current date (today) are retrieved in order to udpate daily statistics.

### Missing FEATUREs and BUGs list

- [ ] Fix stylesheets, they are ugly
- [ ] History, DbManager: add feature to add and edit comments
- [ ] TimeTracker: add feature, when db is not available then store into external CSV (and also sync this file with db)

## Documentation

This README file is the official source of information

## Contribute

Please read the CONTRIBUTE file for guidelines. Thanks for your help!

## Licensing

The *YE.A.S.T.* software is licensed under the [GNU General Public License Version 3](http://www.gnu.org/licenses/gpl.html). 
Please refer to LICENSE file for details.
