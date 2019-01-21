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

--> Example of valid line :  

./bowling_score XXXXXXXXXXXX  
300  
./bowling_score 5/5/5/5/5/5/5/5/5/5/5  
150  
./bowling_score 54-54-54-54-54-54-54-54-54-54-  
90  
./bowling_score X54-6/36-X9/81-4/XX81  
164  

Unit tests are available with the excutable :  
./bowling_tests  
