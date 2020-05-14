# 2020-pd2-sokoban
## Video link
## How to play
### Use arrow keys to move the character
### In-game keys:
Press R to open reset menu.  
Press Q to open quit menu.
## Features
### Main menu
Four buttons:  
START: Go to select level menu.  
QUIT: Quit the game.  
SHOW RECORD: View statistics.  
SECRET BUTTON: Hidden beneath our naked eyes.
### Real time timer and step counter
They are at the botttom of the UI while playing.  
Unfortunately, real time timer is bugged.  
I need to optimize my program to get it back working.  
### Saved game
View all statistics at main menu.
## Bonus
### Load map from files
aka posible to add custom maps.  
Please refer to level encoding rules and map codes if you want to add custom maps.
### A secret
A reference to the past.
## level encoding rules
Here are rules if you want to add custom maps.  
Type each code in the following format.  
A number with a space before and after it  
e.g. , " 0 0 0 0 0 0" ... ,  
and only 10 * 10 (100) numbers are allowed  
since I didn't plan to make full customization.  
### map codes
0 : air (no blocks)  
1 : ground (walkable block)  
2 : wall (to enclose the map)  
3 : target (the goal is to move the box on top of it)  
4 : box (it's a box!)  
5 : player (choose where to place player when the map is loaded)  
6 : player + target (sometimes, a map just have player and target on the same block)  
7 : box + target (this map is so good that it just placed box and target on the same block)  
## references
### my friend, Cang-yu Lin from TKU
He helped me write the mainframe of this project.
### Qt Documentation
Of course.
### Qt forum
It helped me solve lots of strange problems.
### Stackoverflow
It is as important as Qt forum.
### Soko++ on the google play
All 10 maps come from this app , from Microban III and Microban IV in the app.
### JSoko
because I am so bad that couldn't solve the map I chose,  
I used this app to solve it for me.
### Google
thanks for the search engine  
and all of images come from google,too.
