#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int my_strcmp(char* s1, char* s2) {
    int ctr;
    for (ctr = 0; s1[ctr] != 0 && s2[ctr] != 0; ctr++) { 
        if ((int)s1[ctr] < (int)s2[ctr]) {
            return -1;
        }
        else if ((int)s1[ctr] > (int)s2[ctr]) {
            return 1;
        }
    }
    if (s1[ctr] != 0 && s2[ctr] != 0) {
        return 0;
    }
    else if (s1[ctr] != 0) {
        return 1;
    }
    else if (s2[ctr] != 0) {
        return -1;
    }
    return 0;
}

int wpp_calc(char* s1, char* s2) {
    int wpp_ctr = 0;
    for (int ctr = 0; s1[ctr] != 0 && s2[ctr] != 0; ctr++) { 
        if ((int)s1[ctr] == (int)s2[ctr]) {
            wpp_ctr++;
        }
    }
    return wpp_ctr;
}

// does not work as intended
int mpp_calc(char* s1, char* s2) {
    int mpp_ctr = 0;
    for (int ctr = 0; s1[ctr] != 0 && s2[ctr] != 0; ctr++) { 
        for (int ctr_2 = 0; s1[ctr_2] != 0; ctr_2++) { 
            if (ctr != ctr_2 && (int)s2[ctr] == (int)s1[ctr_2]) {
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
        // printf("Character value %c: %i\tctr: %d\n", s1[ctr], s1[ctr], ctr);
        if ((int)s1[ctr] < 48 || (int)s1[ctr] > 55) {
            return 0;
        }
    }
    // printf("%d\n", ctr);
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

int main(int ac, char** av) {
    char* code = random_code_generator(); // randomly generated code
    int attempts = 10;
    for (int i = 1; i < ac; i += 2) {
        if (av[i][1] == 't') {
            attempts = atoi(av[i+1]);
        }
        else if (av[i][1] == 'c') {
            code = av[i+1];
        }
    }

    printf("Attempts: %d\nCode: %s\n", attempts, code);
    // char input;
    // Go through each attempt
    for (int att = 0; att < attempts; att++) {
        // printf("att: %d /  attempts: %d\n", att, attempts);
        printf("---\nRound %d\n", att);
        // char* guess = &input;
        char guess[100];
        while (1) {
            // scanf("%s", &input); //cannot use scanf
            
            // char buffer[10];
            // read(STDIN_FILENO, guess, 10);
            read(0, guess, 100);
            // printf("%s\n", guess);

            // check if code is valid
            if (valid(guess) == 1) {
                break;
            }
            printf("Wrong input!\n");
        }
        int wpp = wpp_calc(code, guess); // function to count well placed pieces
        int mpp = mpp_calc(code, guess); // function to count misplaced pieces
        // if (my_strcmp(code, guess) == 0) { // guessed code correctly
        if (wpp == 4) {
            printf("Congratz! You did it!\n");
            break;
        }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wpp, mpp);
    }
    return 0;
}