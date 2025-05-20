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

//�Ֆʂ̐���
void ReversiGame::make_board() {

	board[3][3] = 1;
	board[4][4] = 1;
	board[3][4] = -1;
	board[4][3] = -1;
}

//�Ֆʂ̕\��
void ReversiGame::show_board() {
	cout << "   0  1  2  3  4  5  6  7\n";
	for (int i = 0; i < 8; i++) {
		cout << " +--+--+--+--+--+--+--+--+\n" << i << "|";
		for (int j = 0; j < 8; j++) {
			switch (board[i][j]) {
			case -1:
				cout << "��|";
				break;
			case 1:
				cout << "�Z|";
				break;
			default:
				cout << "�@|";
				break;
			}
		}
		cout << "\n";
	}
	cout << " +--+--+--+--+--+--+--+--+\n";
}

//��Ԃ̕\��
void ReversiGame::show_player() {
	switch (player) {
	case -1:
		cout << "���(��)�̎�Ԃł�\n";
		break;
	case 1:
		cout << "���(��)�̎�Ԃł�\n";
		break;
	default:
		cout << "error\n";
		break;
	}
}

//����̍��W�������̕����ɋ��߂邩����
int ReversiGame::check_dir(int i, int j, int dir_i, int dir_j) {
	//���̈ʒu���͈͊O�̏ꍇ�́A0 ��Ԃ��܂��B
	if (i + dir_i < 0 || i + dir_i >= boardSize || j + dir_j < 0 || j + dir_j >= boardSize) {
		return 0;
	}

	//�w�肵�������ɑ���̐΂�����ꍇ�́A�`�F�b�N�ɐi�݂܂�
	if (board[i + dir_i][j + dir_j] == player * -1) {
		int times = 1;
		while (i + dir_i * times >= 0 && i + dir_i * times < boardSize &&
			j + dir_j * times >= 0 && j + dir_j * times < boardSize &&
			board[i + dir_i * times][j + dir_j * times] == player * -1) {
			times++;
		}

		//�w�肳�ꂽ�����̍Ō�̈ʒu�Ƀv���C���[�̐΂�����ꍇ
		if (i + dir_i * times >= 0 && i + dir_i * times < boardSize &&
			j + dir_j * times >= 0 && j + dir_j * times < boardSize &&
			board[i + dir_i * times][j + dir_j * times] == player) {
			//���̊Ԃ̑���̐΂̐���Ԃ�
			return times - 1;
		}
	}

	//�w�肵�������ɑ���̐΂�������Ȃ������ꍇ�́A0��Ԃ��܂��B
	return 0;
}

//����̏ꏊ�ɒu�����Ƃ��ł��邩����
bool ReversiGame::check_plc(int i, int j) {
	//�ꏊ����ł��邩�ǂ���
	if (board[i][j] == 0) {
		//�S������T��
		for (int dir_i = -1; dir_i < 2; dir_i++) {
			for (int dir_j = -1; dir_j < 2; dir_j++) {
				if (check_dir(i, j, dir_i, dir_j)) {
					//�z�u�\�ł����true��Ԃ�
					return true;
				}
			}
		}
	}
	return false;
}

//�I������
bool ReversiGame::flag_fin() {
	//�u����ꏊ�����邩����
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				return true;
			}
		}
	}

	//�v���C���[��ς��Ēu����ꏊ�����邩����
	player *= -1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_plc(i, j)) {
				cout << "�u���ꏊ���Ȃ�����Player��ύX���܂���\n";
				return true;
			}
		}
	}

	return false;
}

//�΂�z�u����
void ReversiGame::place_stn(int i, int j) {
	//�������ɑ���
	for (int dir_i = -1; dir_i < 2; dir_i++) {
		for (int dir_j = -1; dir_j < 2; dir_j++) {
			//���񂾐΂̐�
			int change_num = check_dir(i, j, dir_i, dir_j);
			//���񂾐΂̐������u��������
			for (int k = 1; k < change_num + 1; k++) {
				board[i + dir_i * k][j + dir_j * k] = player;
			}
		}
	}
	//�z�u�ӏ���u��������
	board[i][j] = player;
}

//���s����
void ReversiGame::judge_board() {
	int count_b = 0; //���΂̐�
	int count_w = 0; //���΂̐�
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
	//���ʕ\��
	cout << "���" << count_b << ":���" << count_w << "\n";
	//���s����
	if (count_b > count_w) {
		cout << "���̏���\n";
	}
	else if (count_w > count_b) {
		cout << "���̏���\n";
	}
	else {
		cout << "��������\n";
	}
}

void ReversiGame::enemyMove() {
	int i, j;
	do {
		i = rand() % boardSize;
		j = rand() % boardSize;
	} while (!check_plc(i, j));

	cout << "�G�� " << i << "-" << j << "�ɐ΂�u���܂���\n";
	place_stn(i, j);
}


void ReversiGame::play() {
	while (flag_fin()) {
		show_board();
		show_player();

		if (player == -1) {
			int i, j;
			do {
				cout << "�z�u�ꏊ����͂��Ă�������\n" ;
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

