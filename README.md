# CCA
"CCA" or "Cryptographic Cellular Automaton" is an exploration of a - most likely stupid - Idea I had a while ago.
The idea was to use the chaotic behaviour* of celular automata under certain rule sets for applications such as RNG, Hashing and even encryption. 

*: _Is it actually chaotic? I haven't checked, but it looks pretty chaotic to the naked eye, doesn't it?_

I am of course not claiming that this is viable - in all likelihood it isn't.

I haven't done proper analysis of the RNG to quatify its' properties**, nor have I spend any time checking whether my idea for hashing actually produces decent results (I haven't checked for colisions, etc.). Much less would I recommend anyone actually using this little encryption scheme for anything important.

This is purely a little exercise for me to keep coding in my free time.

**: I did however run the DIEHARDER test suite on my generator and the current implementation passes most tests therein. The results, currently uncommented on, can be found under /Documentation/Validation/. They have all been generated using the test_dieharder.sh bash-script, their file names are the seeds used to seed the generator (using /src/tests/Test_Dieharder.cpp). These validation tests should therefore be recreatable. I may, or may not, do further analysis in the future. Cyclelength analysis has been attempted, but so far with little sucess.
