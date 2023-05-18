#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>
#include "forca.h"

//global variables
char secretword[WORD_LENGTH];
char guesses[26];
int givenguesses = 0;

int guessedright() {
    for (int i = 0; i < strlen(secretword); i++) {
        if (!alreadyguessed(secretword[i])) {
            return 0;
        }
    }
    return 1;
}

int wrongguesses() {
    int misses = 0;
    for (int i = 0; i < givenguesses; i++) {
        int exist = 0;
        for (int j = 0; j < strlen(secretword); j++) {
            if (toupper(guesses[i]) == secretword[j]) {
                exist = 1;
                break;
            }
        }
        if (!exist) misses++; 
    }
    return misses;
}

int hang() {
    return wrongguesses() >= 6;
}

void opening() {
    printf ("***************\n");
    printf ("  Hungman Game \n");
    printf ("***************\n\n");
}

int alreadyguessed(char letter) {
    int findit = 0;

    for (int j=0; j<givenguesses; j++) {
        if (toupper(guesses[j]) == letter) {
            findit = 1;
            break;
        }
    }

    return findit;
}

void guessnow() {
    char guess;
    printf ("Type a letter: ");
    scanf(" %c", &guess);

    guesses[givenguesses] = guess;
    givenguesses++;
}

void drawhungman() {
    int misses = wrongguesses();

    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (misses>=1?'(':' '), 
        (misses>=1?'_':' '), (misses>=1?')':' '));
    printf(" |      %c%c%c  \n", (misses>=3?'\\':' '), 
        (misses>=2?'|':' '), (misses>=4?'/': ' '));
    printf(" |       %c     \n", (misses>=2?'|':' '));
    printf(" |      %c %c   \n", (misses>=5?'/':' '), 
        (misses>=6?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");

    for (int i=0; i<strlen(secretword); i++) {

        int findit = alreadyguessed(secretword[i]);

        if (findit) {
            printf ("%c ", secretword[i]);
        } else {
            printf ("_ ");
        }
        }
        printf ("\n");
}

void addword () {
    char want;
    printf ("Do you want to add a new word in the game? (Y/N) ");
    scanf (" %c", &want);

    if (toupper(want) == 'Y') {
        char newword[WORD_LENGTH];
        printf ("What's the new word? ");
        scanf ("%s", newword);
        strupr(newword);

        FILE* f;
        f = fopen("words.txt", "r+");
        if (f == 0) {
            printf ("Sorry, unavailable database! \n\\n");
            exit(1);
        }

        int qtt;
        fscanf (f, "%d", &qtt);
        qtt++;

        fseek (f, 0, SEEK_SET);
        fprintf (f, "%d", qtt);

        fseek (f, 0, SEEK_END);
        fprintf (f, "\n%s", newword);

        fclose(f);
    }

}

void chooseword () {
    FILE* f;
    f = fopen ("words.txt", "r");

    int nofwords;
    fscanf(f, "%d", &nofwords);
    if (f == 0) {
        printf ("Sorry, unavailable database! \n\\n");
        exit(1);
    }
    srand(time(0));
    int randomic = rand() % nofwords;

    for (int i = 0; i <= randomic; i++) {
        fscanf (f, "%s", secretword);
    }

    fclose(f);
}

int main() {
    
    chooseword(secretword);
    opening();

    do
    {
        drawhungman();
        guessnow();
        system("cls");
    } while (!guessedright() && !hang());

    if (guessedright()) {
        printf("\nCongratulations, you win!\n\n");

        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.    \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /      \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n\n");
    } else {
        printf("\nOh no, you were hung!\n");
        printf("The word was **%s**\n\n", secretword);

        printf("    _______________         \n");
        printf("   /               \\       \n"); 
        printf("  /                 \\      \n");
        printf("//                   \\/\\  \n");
        printf("\\|   XXXX     XXXX   | /   \n");
        printf(" |   XXXX     XXXX   |/     \n");
        printf(" |   XXX       XXX   |      \n");
        printf(" |                   |      \n");
        printf(" \\__      XXX      __/     \n");
        printf("   |\\     XXX     /|       \n");
        printf("   | |           | |        \n");
        printf("   | I I I I I I I |        \n");
        printf("   |  I I I I I I  |        \n");
        printf("   \\_             _/       \n");
        printf("     \\_         _/         \n");
        printf("       \\_______/           \n");
    }
    
    addword();
}