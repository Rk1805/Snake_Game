# Snake_Game
This file contains the code for the snake game. 

The snake game is a classic arcade game which initially launched in 1970's where the player 
controls a growing snake, guiding it to collect food while avoiding collisions with itself 
and the walls of the game area. It was much popular in the keypad phones.


This file contains two seperate code for macos and windows environment because some header files like
termios.h are of a great use but works only on macos. An alternative conio.h and windows.h library has been added in the 
code so as to replicate the code initially written in macos

First step is to run the code in your system. When you run the code, a interface appears where you have the options to 
play the game, select maps, change speed, some basic insrtrction to play the game. One cool feature is that 
you can view your top 10 high scores in a specific map.

/Users/rishi/Desktop/Screenshot 2024-03-18 at 2.19.36 AM.png

To select any of the options, enter the number mapped to it and press enter.
For example, if you want to change the speed, enter 3 and press enter. It will display thw options 
change your speed. Same is the case with other options.

This game has 3 maps designed to play. Classic Box, 
which is the classic map, Compartment and Apartment.

To perform a particular change in the default value of the speed or change the map, enter 
the number mapped to it and press enter. 

When you start a new game, initially the snake will always be at centre.
You can move the snake by the keys 'w'(front),'s'(back),'a'(left) and 'd'(right).
Your aim in the game is to eat as many fruits as possible before the game is over.
To eat fruit, you simply need to do over the fruit. In this process, the length of snake increases by one unit.
To pause the quit game in middle, press 'x'. It will ask you if you really want to quit the game.

You can check your high scores of all time(even after you quit the game) by going to high score. To check high scores of other map,
select that map first and then view high scores again.
