# Magnetize

Magnetize is a two player game, with one player "white" and one player "black", where the two players alternate turns dropping their pieces onto a board,
like in Connect Four. Whichever player accumulates a square of their pieces first wins. However, the game has the added complexity of a "magnetize" function, where
instead of dropping a piece a player may turn on his "magnet" and all of his pieces will be magnetically pulled towards his side, right for white and black for left. 
When a player turns on his magnet he forfeits a certain number of turns, defined by the "maglock" value. When maglock is over the magnet is turned off, his pieces are
again affected by gravity, and the player can once again drop pieces.

To start the game, enter `./play -h 4 -w 4 -s 2 -l 2 -b`. The value after `h` represents the height, `-w` the width, `-s` the size of the square needed to win,
and `-l` the maglock length. `-b` means the board will be represented as bits behind the scenes, the more memory efficient option. 
The other option is `-m`, a matrix representation of the board. Neither option
affects the player's experience. 

To start the board will look like this 

```
  0123

0 ....
1 ....
2 ....
```

Black goes first. Suppose he enters `2` for column 2. Now the board looks like
```
  0123

0 ....
1 ....
2 ....
3 ..*.
```

White goes and enters `2`. Now his piece is stacked upon black's.
```
  0123

0 ....
1 ....
2 ..o.
3 ..*.
```

Now black enters `2` again.
```
  0123

0 ....
1 ..*.
2 ..o.
3 ..*.
```

And white also enters `2` again. 
```
  0123

0 ..o.
1 ..*.
2 ..o.
3 ..*.
```

Now, black uses his magnet by entering `!`. See that black's pieces have been magnetized to the left, and white's pieces have fallen now that they are no longer supported
by the black pieces.
```
  0123

0 ....
1 *...
2 ..o.
3 *.o.
```

White enters `3`
```
  0123

0 ....
1 *...
2 ..o.
3 *.oo
```

And then white enters `3` again. Black's pieces are still magnetized and he has forfitted his turn.  
```
  0123

0 ....
1 ....
2 *.oo
3 *.oo
```

White has won because he created a 2x2 square of white pieces! The game is over.
