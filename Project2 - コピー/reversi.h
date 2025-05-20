#ifndef REVERSIGAME_H
#define REVERSIGAME_H

class ReversiGame {
private:
    static const int boardSize = 8;
    int board[boardSize][boardSize] = {};
    int player = -1;


    void make_board();
    void show_board();
    void show_player();
    int check_dir(int i, int j, int dir_i, int dir_j);
    bool check_plc(int i, int j);
    bool flag_fin();
    void place_stn(int i, int j);
    void judge_board();
    void enemyMove();

public:
    ReversiGame();
    void play();
};

#endif 
