#include "reversi.h"
#include <iostream>
#include <cstdlib>
#include <ctime>


using namespace std;

int board[8][8] = {};

int player = -1;

ReversiGame::ReversiGame() {
	make_board();
}

//盤面の生成
void ReversiGame::make_board() {

	board[3][3] = 1;
	board[4][4] = 1;
	board[3][4] = -1;
	board[4][3] = -1;
}

//盤面の表示
void ReversiGame::show_board() {
	cout << "   0  1  2  3  4  5  6  7\n";
	for (int i = 0; i < 8; i++) {
		cout << " +--+--+--+--+--+--+--+--+\n" << i << "|";
		for (int j = 0; j < 8; j++) {
			switch (board[i][j]) {
			case -1:
				cout << "●|";
				break;
			case 1:
				cout << "〇|";
				break;
			default:
				cout << "　|";
				break;
			}
		}
		cout << "\n";
	}
	cout << " +--+--+--+--+--+--+--+--+\n";
}

//手番の表示
void ReversiGame::show_player() {
	switch (player) {
	case -1:
		cout << "先手(白)の手番です\n";
		break;
	case 1:
		cout << "後手(黒)の手番です\n";
		break;
	default:
		cout << "error\n";
		break;
	}
}

//特定の座標から特定の方向に挟めるか判定
int ReversiGame::check_dir(int i, int j, int dir_i, int dir_j) {
	//次の位置が範囲外の場合は、0 を返します。
	if (i + dir_i < 0 || i + dir_i >= boardSize || j + dir_j < 0 || j + dir_j >= boardSize) {
		return 0;
	}

	//指定した方向に相手の石がある場合は、チェックに進みます
	if (board[i + dir_i][j + dir_j] == player * -1) {
		int times = 1;
		while (i + dir_i * times >= 0 && i + dir_i * times < boardSize &&
			j + dir_j * times >= 0 && j + dir_j * times < boardSize &&
			board[i + dir_i * times][j + dir_j * times] == player * -1) {
			times++;
		}

		//指定された方向の最後の位置にプレイヤーの石がある場合
		if (i + dir_i * times >= 0 && i + dir_i * times < boardSize &&
			j + dir_j * times >= 0 && j + dir_j * times < boardSize &&
			board[i + dir_i * times][j + dir_j * times] == player) {
			//その間の相手の石の数を返す
			return times - 1;
		}
	}

	//指定した方向に相手の石が見つからなかった場合は、0を返します。
	return 0;
}

//特定の場所に置くことができるか判定
bool ReversiGame::check_plc(int i, int j) {
	//場所が空であるかどうか
	if (board[i][j] == 0) {
		//全方向を探索
		for (int dir_i = -1; dir_i < 2; dir_i++) {
			for (int dir_j = -1; dir_j < 2; dir_j++) {
				if (check_dir(i, j, dir_i, dir_j)) {
					//配置可能であればtrueを返す
					return true;
				}
			}
		}
	}
	return false;
}

//終了判定
bool ReversiGame::flag_fin() {
	//置ける場所があるか判定
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				return true;
			}
		}
	}

	//プレイヤーを変えて置ける場所があるか判定
	player *= -1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				cout << "置く場所がないためPlayerを変更しました\n";
				return true;
			}
		}
	}

	return false;
}

//石を配置する
void ReversiGame::place_stn(int i, int j) {
	//方向毎に走査
	for (int dir_i = -1; dir_i < 2; dir_i++) {
		for (int dir_j = -1; dir_j < 2; dir_j++) {
			//挟んだ石の数
			int change_num = check_dir(i, j, dir_i, dir_j);
			//挟んだ石の数だけ置き換える
			for (int k = 1; k < change_num + 1; k++) {
				board[i + dir_i * k][j + dir_j * k] = player;
			}
		}
	}
	//配置箇所を置き換える
	board[i][j] = player;
}

//勝敗判定
void ReversiGame::judge_board() {
	int count_b = 0; //黒石の数
	int count_w = 0; //白石の数
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (board[i][j] == -1) {
				count_b++;
			}
			else if (board[i][j] == 1) {
				count_w++;
			}
		}
	}
	//結果表示
	cout << "先手" << count_b << ":後手" << count_w << "\n";
	//勝敗判定
	if (count_b > count_w) {
		cout << "先手の勝利\n";
	}
	else if (count_w > count_b) {
		cout << "後手の勝利\n";
	}
	else {
		cout << "引き分け\n";
	}
}

void ReversiGame::enemyMove() {
	int i, j;
	do {
		i = rand() % boardSize;
		j = rand() % boardSize;
	} while (!check_plc(i, j));

	cout << "敵は " << i << "-" << j << "に石を置きました\n";
	place_stn(i, j);
}


void ReversiGame::play() {
	while (flag_fin()) {
		show_board();
		show_player();

		if (player == -1) {
			int i, j;
			do {
				cout << "配置場所を入力してください\n" ;
				cin >> i >> j;
			} while (!check_plc(i, j));

			place_stn(i, j);
		}
		else {
			enemyMove();
		}

		player *= -1;
	}

	show_board();
	judge_board();
}

