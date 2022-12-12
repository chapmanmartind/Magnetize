#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "logic.h"
#include "board.h"

//plays the game//
int main(int argc, char* argv[]) {
    unsigned int height;
    unsigned int width;
    unsigned int square;
    unsigned int maglock;
    enum type game_type;
    
    for (unsigned int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-h") == 0) {
            height = atoi(argv[i+1]);  
        }
        if (strcmp(argv[i], "-w") == 0) {
            width = atoi(argv[i+1]);
        }
        if (strcmp(argv[i], "-s") == 0) {
           square = atoi(argv[i+1]);
        }
        if (strcmp(argv[i], "-l") == 0) {
           maglock = atoi(argv[i+1]);
        }
        
        if (strcmp(argv[i], "-m") == 0) {
            game_type = MATRIX;
        }
        if (strcmp(argv[i], "-b") == 0) {
            game_type = BITS;
        }
    }
    game* main_game = new_game(square, maglock, width, height, game_type);
    
    while (game_outcome(main_game) == IN_PROGRESS) {
        board_show(main_game->b);
        char ch;
        if (main_game->player == BLACKS_TURN) {
            printf("Black: \n");
        }
        else {
            printf("White: \n");
        }
        scanf("%c%*c", &ch);
        printf("\n");
        unsigned int column = 100;
        char* char_list = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!";
        for (unsigned int i = 0; i < strlen(char_list); i++) {
            if (char_list[i] == ch) {
                column = i;
                break;
            }
        }
        if ((column == 100) || ((column >= width) && (column != 62))) {
            printf("Invalid column, please try again \n");
        }
        else {
            if (column == 62) {
                magnetize(main_game);
            }
            else {
                pos position;
                position.r = 0;
                position.c = column;
                if (board_get(main_game->b, position) != EMPTY) {
                    printf("Column already full, try again \n");
                }
                else {
                    drop_piece(main_game, column);
                }
            }
        }
    }
    if (game_outcome(main_game) == BLACK_WIN) {
        printf("Game over. Winner: Black \n");
    } 
    else if (game_outcome(main_game) == WHITE_WIN) {
        printf("Game over. Winner: White \n");
    }
    else {
        printf("Game over. Draw \n \n");
    }
    board_show(main_game->b);
    game_free(main_game);    
    return 0;
}












