#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "pos.h"
#include "board.h"
#include "logic.h"

/*testing board_new, board_free, board_show */
void board_test() {
    
    pos pos1;
    pos1.r = 3;
    pos1.c = 3;
    
    pos pos2; 
    pos2.r = 0;
    pos2.c = 3;
    /*
    board* game_board = board_new(10, 10, MATRIX);
    board_show(game_board);
    
    board_set(game_board, pos1, WHITE);
    board_show(game_board);
    
    board_free(game_board);
    */
    board* game_board = board_new(4, 3, BITS);
    board_show(game_board);
    /*
    board_set(game_board, pos1, WHITE);
    board_set(game_board, pos2, BLACK);
    board_show(game_board);
    board_set(game_board, pos1, EMPTY);
    board_show(game_board);
    free(game_board);
    */
    //printf("%d", board_get(game_board, pos1) == 0);
}

//tests logic functions
void logic_test() {
    
    /* 
    game* fresh_game = new_game(2, 2, 10, 10, MATRIX);
    drop_piece(fresh_game, 5);
    drop_piece(fresh_game, 5);
    drop_piece(fresh_game, 5);
    drop_piece(fresh_game, 5);
    drop_piece(fresh_game, 5);
    drop_piece(fresh_game, 4);
    drop_piece(fresh_game, 4);
    drop_piece(fresh_game, 4);
    board_show(fresh_game->b);
    
    game* test_game = new_game(2, 2, 4, 4, MATRIX);
    drop_piece(test_game, 0);
    drop_piece(test_game, 3);
    drop_piece(test_game, 1);
    drop_piece(test_game, 2);
    drop_piece(test_game, 1);
    drop_piece(test_game, 2);
    drop_piece(test_game, 2);
    drop_piece(test_game, 1);
    board_show(test_game->b);
    magnetize(test_game);
    board_show(test_game->b); 
    */
    /*
    game* test_game3 = new_game(2, 2, 10, 10, MATRIX);
    drop_piece(test_game3, 0);
    drop_piece(test_game3, 0);
    drop_piece(test_game3, 1);
    board_show(test_game3->b);
    magnetize(test_game3);
    board_show(test_game3->b);
    drop_piece(test_game3, 0);
    board_show(test_game3->b);
    drop_piece(test_game3, 0);
    board_show(test_game3->b);
    drop_piece(test_game3, 9);
    board_show(test_game3->b);
    */

    //game* test_game2 = new_game(2, 2, 4, 4, MATRIX);
    //drop_piece(test_game2, 0);
    //drop_piece(test_game2, 3);
    //drop_piece(test_game2, 0);
    //drop_piece(test_game2, 3);
    //drop_piece(test_game2, 1);
    //drop_piece(test_game2, 2);
    //drop_piece(test_game2, 1);
    //drop_piece(test_game2, 2);
    //board_show(test_game2->b);
    
    game* test_game4 = new_game(2, 2, 5, 4, MATRIX);
    drop_piece(test_game4, 1);
    board_show(test_game4->b);
    drop_piece(test_game4, 3);
    board_show(test_game4->b);
    drop_piece(test_game4, 0);
    board_show(test_game4->b);
    drop_piece(test_game4, 1);
    board_show(test_game4->b);
    drop_piece(test_game4, 1);
    board_show(test_game4->b);
    drop_piece(test_game4, 4);
    board_show(test_game4->b);
    drop_piece(test_game4, 3);
    board_show(test_game4->b);
    drop_piece(test_game4, 3);
    board_show(test_game4->b);
    drop_piece(test_game4, 3);
    board_show(test_game4->b);
    magnetize(test_game4);    
    board_show(test_game4->b);
    drop_piece(test_game4, 2);
    board_show(test_game4->b);
    drop_piece(test_game4, 4);
    board_show(test_game4->b);
    magnetize(test_game4);    
    board_show(test_game4->b);
    drop_piece(test_game4, 3);
    board_show(test_game4->b);
    outcome res = game_outcome(test_game4);
    
    printf("%d", res);
}

int main(int argc, char* argv[]) {
    board_test();
    //logic_test();
    return 0;
}



