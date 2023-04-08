# C-GOL
C-GOL, Crypto-GOL or Crypto-Game-of-Life is an exploration of a - most likely stupid - Idea I had a while ago.
The idea was to use the chaotic behaviour of celular automata under certain rule sets for applications such as RNG and Hashing. 
I am of course not claiming that this is viable - in all likelihood it isn't.
I haven't done proper analysis of the RNG to quatify its' properties, nor have I spend any time checking whether my idea for hashing actually produces decent results.
This is purely a little exercise for me to keep coding in my free time.

## Classes
Here's a list of classes in this project.
### BitBoard
Basically a wrapper for a dynamic bitset for it to act as a two dimensional grid. 
Providing the necessary methods for manipulation of such a two dimensional bit grid.
Also includes neighbour countnig functionality (currently for Moore and von Neumann neighbourhoods).
### GOL
Conway's Game of Life class. 
Provides basic functionality to run Conway's Game of Life on different sized grids. 
The grid is provided by an instance of the BitBoard class.
### C-GOL
"Cryptographic" Game of Life - inherits from GOL.
Modifies the GOL class for further use in RNG and hashing.
Treats seeds different and uses a different rule set; also provides a function to retrieve random bitstrings.
### GOL-RNG
Game of Life Random Number Generator - inherits from C-GOL. 
Provides RNG functionality such as random integer, random float, random bit, etc.
### GOL-Hash
Game of Life Hashing - inherits from C-GOL. 
Provides hashing functionality.

## Folder Structure
### Source
The source files are split up between the header folder (containing the headers) and the src folder (containing the source files).
### Tests & Demos
In the tests folder there are various test programms testing and demonstrating the various functionalities.
### Libraries & Excecutables
The Makefile provided will move the compiled library files to a lib folder and the compiled excecutables to a exces folder.
