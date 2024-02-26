# C-GOL
C-GOL, Crypto-GOL or Crypto-Game-of-Life is an exploration of a - most likely stupid - Idea I had a while ago.
The idea was to use the chaotic behaviour* of celular automata under certain rule sets for applications such as RNG, Hashing and even encryption. 

*:_Is it actually chaotic? I haven't checked, but it looks pretty chaotic to the naked eye, doesn't it?_

I am of course not claiming that this is viable - in all likelihood it isn't.

I haven't done proper analysis of the RNG to quatify its' properties, nor have I spend any time checking whether my idea for hashing actually produces decent results. Much less would I recommend anyone actually using this little encryption scheme for anything important.

This is purely a little exercise for me to keep coding in my free time.

## Classes
Here's a list of classes in this project.
### GOL_Board (Template)
Base GOL_Board class template - using bitwise operations to run binary celular automata.
#### Flexible_GOL_Board (Template)
Inherits from GOL_Board - most flexible, but slowest, implementation of binary celular automata.
Allows customization of the rules (creation and survival rules - see documentation) even at runtime.
#### Classic_GOL_Board (Template)
Inherits from GOL_Board - faster implementaiton of binary celular automata, implements the classic rules of Conway's Game of Life.
#### Cryptographic_GOL_Board
Inherits from GOL_Board - fast implementaiton of binary celular automata, implements custom rules.
Later used for RNG, Hashing and Keygen.
### GOL-RNG
Game of Life Random Number Generator. 
Provides RNG functionality such as random integer, random float, random bit, etc.
### GOL-Hash
Game of Life Hashing. 
Provides hashing functionality.
### GOL-Keygen
Key extention/streching class.
### GOL_Enc
Encryption class, uses Keygen class to generate a key, then XORs it with the input data. Essentially a stream cypher using the keygen class to generate the key.

## Folder Structure
### Documentation
Documentation will be added to the "./Documentation" folder.
### Source
The source files are split up between the header folder (containing the headers) and the src folder (containing the source files).
### Tests & Demos
In the tests folder there are various test programms testing and demonstrating the various functionalities.
#### Test Data
The tests assume the existance of a folder called "test_data". This data is not provided here.
### Libraries & Excecutables
The Makefile provided will move the compiled library files to a lib folder and the compiled excecutables to a exces folder.

## Future Ideas
- Some optimization
- Tweaks to the Cryptographic_GOL class; maybe a permutation of the rows on the board after every _n_ steps?
- Block-cypher scheme based on this idea?