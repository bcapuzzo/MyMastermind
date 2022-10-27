# my_mastermind

## Functionalities

The mastermind program is a game modeled after a board game with colored balls, but
her uses the digits 0 through 7 instead. After starting the program, the user enters
a certain number of guesses to try and determine the secret code. The secret code is
4 digits long and only consists of the digits 0 through 7. Numbers can be repeated 
within the code. Example secret codes would be 7254, 3526, 1126, and 5555. The 
mastermind program is able to deal with many different inputs and scenarios. The helper 
function to test validity ensures that the code entered can be compared to the secret 
code. Otherwise, the user will be prompted to enter a new code. The program also makes 
sure that the guess only contains four digits. If the code is guessed correctly before 
reaching the allowed number of guesses, then the program stops and congratulates the 
user. Otherwise, if the user reaches the end of his/her attempts without guessing the 
code correctly, the code is revealed to the user.

## Description of Code

The code features the main function that operates the repetition of the mastermind
game by repeating the messages printed to the screen and receiving the guesses. The
program first begins by determining if any values for the secret code or number of
attempts were given initially. Otherwise, a helper function produces a random code
using `time()` and `rand()`/`srand()` and attempts are defaulted to 10. Once guesses are 
receieved, they are sent to a helper function to determine if the guess is valid 
(only contains digits 0, 1, 2, 3, 4, 5, 6, 7) and then sends the guess to two helper 
functions to determine how many digits are guessed correctly (wellplaced pieces) and 
are misplaced digits that exist elsewhere in the secret code (misplaced pieces). The 
program dispalys these statistics before requesting another guess.

## Compilation and Execution

This program uses a make file, which combines all .c files into one executable command.
In order to compile all files in one line, just type make into the command line and then
run the executable file as intended. When running the executable, there are two tag options
for the game. If you enter a -t tag, then you can folow it with a number that represents the
number of attempts you will be given to guess the code. The other tag is -c and you need to 
follow it with a valid four digit code within quotation marks as a string. Valid codes are
explained above (only contains digits 0 through 7) You may use one tag, both tags, or no tags.
Example below:
```sh
$> make
$> ./mastermind
$> ./mastermind -c "0241"
$> ./mastermind -t 15
$> ./mastermind -c "0241" -t 20
```


## Examples of Game

Provided Code, Guessed Correctly
```sh
$> ./mastermind -c "0123" -t 3
Will you find the secret code?
---
Round 0
3210
Well placed pieces: 0
Misplaced pieces: 4
---
Round 1
0124
Well placed pieces: 3
Misplaced pieces: 0
---
Round 2
0123
Congratz! You did it!
```

Secret Code, Guessed Incorrectly
```sh
$> ./mastermind -t 3
Will you find the secret code?
---
Round 0
0123
Well placed pieces: 0
Misplaced pieces: 2
---
Round 1
4326
Well placed pieces: 0
Misplaced pieces: 2
---
Round 2
7245
Well placed pieces: 1
Misplaced pieces: 2
---
You ran out of attempts! :(
The secret code was: 5204
```

## Deals with Incorrect Input & Errors

```sh
$> ./mastermind -t 0
Invalid number of attempts. Provide a positve integer greater than 0.

$> ./mastermind -c "03632"
Invalid Code. Provide a 4 digit code using numbers 0 through 7.

$> ./mastermind
Will you find the secret code?
---
Round 0
tata
Wrong input!
03721
Wrong input!
```
