#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

// function to randomly generate code -- does not work as intended yet
char* random_code_generator() {
    char* secret = (char*)malloc(5*sizeof(char*));
    srand(time(0));
    for (int i = 0; i < 4; i++) {
        int num = rand() % 7;
        secret[i] = (char)num;
    }
    secret[4] = '\0';
    return secret;
}

int main(int ac, char** av) {
    char* code = random_code_generator(); // needs to be a randomly generated code
    int attempts = 10;
    for (int i = 1; i < ac; i += 2) {
        if (av[i][1] == 't') {
            attempts = atoi(av[i+1]);
        }
        else if (av[i][1] == 'c') {
            code = av[i+1];
        }
    }

    printf("Attempts: %d\nCode: %s", attempts, code);
    // printf("%d\n", rand()%10007);

    // Go through each attempt
    for (int att = 0; att < attempts; att++) {
        
        printf("---\nRound %d\n", att);
        char guess;
        scanf("%s", &guess);
        int wpp = 0; // function to count well placed pieces
        int mpp = 0; // function to count misplaced pieces
        // if (my_strcmp(code, guess) == 0) { // guessed code correctly
        //     printf("Congratz! You did it!");
        //     break;
        // }
        printf("Well placed pieces: %d\nMisplaced pieces: %d\n", wpp, mpp);
    }

    return 0;
}