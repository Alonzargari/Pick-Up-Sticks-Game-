OOP PROJECT :README FILE

NAME: ALON ZARGARI 

GENERAL EXPLANATION OF THE EXERCISE:
TITLE: PICK UP STICKS

Here, I implemented the well-known game "Pick Up Sticks." The player's goal is to collect all the 
sticks on the board within a given time limit. Try to achieve the highest score. You can use the 
hint button to know which sticks are currently available. If you get tired, you can save the game 
and return later, starting from a checkpoint. Good luck!

THE FILES WE MAKE:
PickUpStick:

This file is responsible for holding all the data about the current stick. The data is randomly 
generated. It also handles writing the current stick data to the output file. Each stick knows 
its boundary sticks, which helps with updating the sticks.

Board:

This is the main file that includes all the pick-up sticks data structures. The board is 
responsible for updating the sticks on the board and determining the available ones.

Menu:

As the name suggests, this file contains the opening menu with buttons like "Play," "Load Game," and "Exit."

InfoBar:

These files are responsible for showing the time to the player and providing 
information on the ongoing game (such as how many sticks are available and 
how many the player has picked). They also handle displaying the hint button and save button.

SingleTone:

This file manages all the resources in the game and instances, such as showing 
errors from exceptions and displaying the score at the end. It loads all the textures and other resources.

FormatException:

This file is responsible for throwing errors for exceptions (such as a file not opening and more).

MAIN DATA STRUCTURE AND THEIR FUNCTIONS:
For holding all the sticks in the game and the boundary sticks in the PickUpStick class, I used lists:

Lists:
Deleting: O(1)
Finding: O(N)
Insertion: O(N) (Although if the insertion is always at the head or the tail, it is O(1))
For holding the available sticks, I used a multimap. This allows me to keep them sorted by a functor I defined:

Multimap:
Finding: O(log n) (because it is implemented as a red-black tree)
Insertion: O(log n)
Deleting: O(log n)
Printing all the available sticks for the hint button: O(n)
For mapping the colors and scores, I used a map:

Map:
Mapping (on average): O(N)
I mapped the color enums to get the actual data (color and score) and mapped the scores as
 keys with the actual color as the value (for reading from the input file).

NOTEWORTHY ALGORITHMS:

using  stl library algorithms 

KNOWS BUGS:


OTHER NOTES:

