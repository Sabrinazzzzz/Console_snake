//���� ������


#include <stdio.h> //�������� ����������
#include <stdlib.h> //���������� ��� ������ � �-�� system()/rand()
#include <windows.h> //��� ����������� fps
#include <conio.h> //��� ���������� ���-� � ������
#include <time.h> //��� �������

bool gameover; //���������� ���������� ����
const int width = 30; //������ ����
const int height = 30; //������ ����
int x, y, foodX, foodY, score; //���������� ��������� ������, ��� � �������� �������
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //������������ ��� �������� ������
eDirection dir;
int speed;

//�-� ��������� ���������� ��� ������ ����
void Setup() {
	srand(time(NULL));
	gameover = false; //���������� ���� �� ���������
	dir = STOP; //���������� ������ ����� �� ����� (�������� ���������� ����� ������� ������)
	x = (width / 2) - 1; // ��������� ��������� ��������� �� �������� ����
	y = (height / 2) - 1;
	foodX = rand() * 1.0 / RAND_MAX * (width - 2) + 1; //��������� ���������� ��� �� �����
	foodY = rand() * 1.0 / RAND_MAX * (height - 3) + 1;
	score = 0;
}

void Speed() {
	printf("Choose level of difficulty:\n"
		"1 - Easy\n"
		"2 - Middle\n"
		"3 - Hard\n");
	scanf_s("%d", &speed);

}

void setcur(int x, int y)//��������� ������� �� �������  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

//�-� ���������
void Draw() {
	setcur(0, 0);
	//system("cls"); //������� ������
	printf("GADUKA\n\n\n");
	for (int i = 0; i < width; i++)
		printf("#");
	printf("\n");
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 2)
				printf("#");
			if (i == x && j == y)
				printf("0");
			else if (i == foodX && j == foodY)
				printf("@");
			else {
				bool print = false;
				for (int k = 0; k < nTail; k++) {
					if (tailX[k] == j && tailY[k] == i) {
						print = true;
						printf("o");
					}
				}
				if (!print)
					printf(" ");
			}

		}
		printf("\n");
	}
	for (int i = 0; i < width; i++)
		printf("#");
	printf("\n");
	printf("Score: %d\n", score);
}

//�-� ������������ ������� ������
void Input() {
	if (_kbhit()) {
		switch (_getch()) { //���������� ������� �������
		case 'a': //�������� �����
			dir = LEFT;
			break;
		case 'd': //�������� ������
			dir = RIGHT;
			break;
		case 'w': //�������� �����
			dir = UP;
			break;
		case 's': //�������� ����
			dir = DOWN;
			break;
		case 'q': //����� �� ����
			gameover = true;
			break;
		}
	}
}

//�-� �������� ����
void Logic() {

	//��������� ������
	int prevX = tailX[0]; //���������� ������� �� ������
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = y;
	tailY[0] = x;
	for (int i = 1; i < nTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	//�������� ������
	switch (dir) {
	case LEFT:
		y--;
		break;
	case RIGHT:
		y++;
		break;
	case UP:
		x--;
		break;
	case DOWN:
		x++;
		break;
	}

	if (x > (width - 1) || x < 0 || y >(height - 3) || y < 0) { //���� ������ ����� �� �����, �� ���� ��������
		gameover = true;
		printf("GAME OVER HAHAHAHAHA\nYOU'RE A LOSER\n\n\n\n");
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == y && tailY[i] == x) {
			gameover = true;
			printf("GAME OVER HAHAHAHAHA\nYOU'RE A LOSER\n\n\n\n");
		}
	}

	if (x == foodX && y == foodY) { //���� ������ ����� ������
		score++;
		foodX = rand() * 1.0 / RAND_MAX * (width - 2) + 1; //����� ���������� ��� �� �����
		foodY = rand() * 1.0 / RAND_MAX * (height - 3) + 1;
		nTail++;
	}
}

int main() {
	system("color 02"); //���� ���� � ��������
	Setup();
	Speed();
	while (!gameover) { //���� ���� �� ���������
		switch (speed) {
		case 1: Sleep(100);
		case 2: Sleep(50);
		case 3: Sleep(0);
		}
		Draw();
		Input();
		Logic();
	}
	return 0;
}