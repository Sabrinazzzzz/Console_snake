//»гра змейка


#include <stdio.h> //основна€ библиотека
#include <stdlib.h> //библиотека дл€ работы с ф-ми system()/rand()
#include <windows.h> //дл€ регулировки fps
#include <conio.h> //дл€ считывани€ инф-и с клавиш
#include <time.h> //дл€ рандома

bool gameover; //переменна€ завершени€ игры
const int width = 30; //ширина пол€
const int height = 30; //высота пол€
int x, y, foodX, foodY, score; //переменные координат змейки, еды и подсчета желудей
int tailX[100], tailY[100];
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN }; //перечисление дл€ движени€ змейки
eDirection dir;
int speed;

//ф-€ настройки параметров дл€ начала игры
void Setup() {
	srand(time(NULL));
	gameover = false; //изначально игра не завершена
	dir = STOP; //изначально змейка стоит на месте (движение начинаетс€ после нажати€ клавиш)
	x = (width / 2) - 1; // начальное положение кабанчика по середине пол€
	y = (height / 2) - 1;
	foodX = rand() * 1.0 / RAND_MAX * (width - 2) + 1; //рандомное размещение еды по карте
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

void setcur(int x, int y)//установка курсора на позицию  x y 
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

//ф-€ отрисовки
void Draw() {
	setcur(0, 0);
	//system("cls"); //очистка экрана
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

//ф-€ отслеживани€ нажатий клавиш
void Input() {
	if (_kbhit()) {
		switch (_getch()) { //считывание нажати€ клавиши
		case 'a': //движение влево
			dir = LEFT;
			break;
		case 'd': //движение вправо
			dir = RIGHT;
			break;
		case 'w': //движение вверх
			dir = UP;
			break;
		case 's': //движение вниз
			dir = DOWN;
			break;
		case 'q': //выход из игры
			gameover = true;
			break;
		}
	}
}

//ф-€ механики игры
void Logic() {

	//удлинение змейки
	int prevX = tailX[0]; //предыдущий элемент от головы
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

	//движение змейки
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

	if (x > (width - 1) || x < 0 || y >(height - 3) || y < 0) { //если змейка вышла за забор, то игра окончена
		gameover = true;
		printf("GAME OVER HAHAHAHAHA\nYOU'RE A LOSER\n\n\n\n");
	}

	for (int i = 0; i < nTail; i++) {
		if (tailX[i] == y && tailY[i] == x) {
			gameover = true;
			printf("GAME OVER HAHAHAHAHA\nYOU'RE A LOSER\n\n\n\n");
		}
	}

	if (x == foodX && y == foodY) { //если змейка съела желудь
		score++;
		foodX = rand() * 1.0 / RAND_MAX * (width - 2) + 1; //новое размещение еды на карте
		foodY = rand() * 1.0 / RAND_MAX * (height - 3) + 1;
		nTail++;
	}
}

int main() {
	system("color 02"); //цвет фона и символов
	Setup();
	Speed();
	while (!gameover) { //пока игра не завершена
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