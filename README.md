# bowling_test

This program compute the score on american bowling game.

Compilation :

cmake .
make

2 excecutables are provided.

To compute the bowling score, use :
./bowling_score line

The line is composed by :
--> Strike : "X"
--> Spare : "0" to "9" followed by "/". Example : 6/
--> Miss : 2 numbers between "0" and "9" plus sign "-". The sum of the 2 numbers should be less than 10. Example : 54-

Unit tests are available with the excutable :
./bowling_tests
