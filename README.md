# Zork

A C++ implementation of the Zork game. The program construct a Zork environment based on an input xml file and take user inputs as commansd.

Input
-----

The input xml file, passed in as `argv[1]`, contains the information of the game under one giant root node called `map`: the rooms, items, containers, and creatures. The details of the input and game can be found [here](https://engineering.purdue.edu/~smidkiff/ece30862/zork.html).

Run
---

A sample `Makefile` is provided. Running `make` or `make all` in terminal will compile and run the game with `sample.txt.xml` as the input. Other options are `make compile`, `make runSample`, `make runValgrind` and `make clean`. See [`Makefile`](https://github.com/xu932/Zork/blob/master/Makefile) for details.
