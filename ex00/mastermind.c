#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

// Calculates Well Placed Pieces
// s1 is the secret code and s2 is the user's guess
int wpp_calc(char* s1, char* s2) {
    int wpp_ctr = 0;
    for (int ctr = 0; s1[ctr] != 0 && s2[ctr] != 0; ctr++) { 
        if ((int)s1[ctr] == (int)s2[ctr]) {
            wpp_ctr++;
        }
    }
    return wpp_ctr;
}

// Calculates Misplaced Pieces
// s1 is the secret code and s2 is the user's guess
// int mpp_calc(char* s1, char* s2) {
//     int mpp_ctr = 0;
//     for (int ctr = 0; ctr < 4; ctr++) { 
//         for (int ctr_2 = 0; ctr_2 < 4; ctr_2++) { 
            
//             if (ctr != ctr_2 && // if same columns match, then it is a wpp
//                     (int)s2[ctr] == (int)s1[ctr_2] && // makes sure the piece exists somewhere else in code
//                     (int)s2[ctr_2] != (int)s1[ctr_2] && // 
//                     (int)s2[ctr] != (int)s1[ctr]) // 
//                 {
//                 mpp_ctr++;
//                 break;
//             }
//         }
//     }
//     return mpp_ctr;
// }

// REVISED FUNCTION
int mpp_calc(char* s1, char* s2) {
    int mpp_ctr = 0;
    // integer array tracks if a location of code has already been used for a misplaced piece
    int* locations = malloc(4*sizeof(int));
    for (int i = 0; i < 4; i++) {
        if ((int)s2[i] == (int)s1[i]) { // the guess for that column is correct
            locations[i] = 1;
        }
        else {
            locations[i] = 0;
        }
    }
    // iterates through each location in the guessed code
    for (int ctr_g = 0; ctr_g < 4; ctr_g++) { 
        for (int ctr_c = 0; ctr_c < 4; ctr_c++) { 
            if ((int)s2[ctr_g] == (int)s1[ctr_c] && // makes sure the piece exists somewhere else in code
                    locations[ctr_c] != 1) { // makes sure location has not already been used for misplaced piece
                locations[ctr_c] = 1;
                mpp_ctr++;
                break;
            }
        }
    }
    return mpp_ctr;
}

int valid(char* s1) {
    int ctr = 0;
    for ( ; ctr < 4 && s1[ctr] != 0; ctr++) { 
        // confirms character is a digit between 0 and 7
        if ((int)s1[ctr] < 48 || (int)s1[ctr] > 55) {
            return 0;
        }
    }
    if (ctr < 4) {
        return 0;
    }
    else if ((int)s1[ctr] >= 32 && (int)s1[ctr] <= 126) {
        return 0;
    }
    return 1;
}

// function to randomly generate code
char* random_code_generator() {
    char* secret = malloc(5*sizeof(char*));
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        int num = rand() % 8;
        secret[i] = (char)(num+48);
    }
    secret[4] = '\0';
    return secret;
}

// only numbers 0 through 7
int main(int ac, char** av) {
    char* code = random_code_generator(); // randomly generated code
    int attempts = 10;
    for (int i = 1; i < ac; i += 2) {
        if (av[i][1] == 't') {
            attempts = atoi(av[i+1]);
            if (attempts < 1) {
                printf("Invalid number of attempts. Provide a positve integer greater than 0.\n");
                return 0;
            }
        }
        else if (av[i][1] == 'c') {
            if (valid(av[i+1]) == 0) {
                printf("Invalid Code. Provide a 4 digit code using numbers 0 through 7.\n");
                return 0;
            }
            code = av[i+1];
        }
    }
    printf("Will you find the secret code?\n");
    // Iterate Through Attempts
    for (int att = 0; att < attempts; att++) {
        printf("---\nRound %d\n", att);
        char guess[100];
        while (1) {
            read(0, guess, 100);
            // check if code is valid
            if (valid(guess) == 1) {
                break;
            }
            printf("Wrong input!\n");
        }
        int wpp = wpp_calc(code, guess); // function to count well placed pieces
        int mpp = mpp_calc(code, guess); // function to count misplaced pieces
        if (wpp == 4) { // all four guessed numbers are correct
            printf("Congratz! You did it!\n");
            return 0;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wpp, mpp); // report results of comparing guess to secret code
    }
    printf("---\nYou ran out of attempts! :(\nThe secret code was: %s\n", code);
    return 0;
}