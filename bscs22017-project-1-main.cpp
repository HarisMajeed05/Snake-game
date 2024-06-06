#include<iostream>
#include<conio.h>
#include<windows.h>
#include<mmsystem.h>
#include<fstream>
#include<cmath>
#include<ctime>
#include<string>
#include<time.h>
#include<iomanip>


using namespace std;
enum Direction{UP,DOWN,LEFT,RIGHT};

struct position
{
	int ri;
	int ci;
};
struct snake
{
	position* ps;
	int size;
	char sym;
	int score;
	Direction dir;
	int LeftKey, RightKey, UpKey, DownKey;
	int ALeftKey, DRightKey, WUpKey, SDownKey;
	int JLeftKey, LRightKey, IUpKey, KDownKey;
	int FLeftKey, HRightKey, TUpKey, GDownKey;
	string pName;
};
struct food
{
	position fp;
	bool isAlive;
	int score;
	char sym;
};

void getRowColbyLeftClick(int& rpos, int& cpos)
{
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	DWORD Events;
	INPUT_RECORD InputRecord;
	SetConsoleMode(hInput, ENABLE_PROCESSED_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS);
	do
	{
		ReadConsoleInput(hInput, &InputRecord, 1, &Events);
		if (InputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			cpos = InputRecord.Event.MouseEvent.dwMousePosition.X;
			rpos = InputRecord.Event.MouseEvent.dwMousePosition.Y;
			break;
		}
	} while (true);
}
void gotoRowCol(int rpos, int cpos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = cpos;
	scrn.Y = rpos;
	SetConsoleCursorPosition(hOuput, scrn);
}
void SetClr(int clr)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), clr);
}


bool isLegalCoordinate(position p,int h,int w, snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		if ((S.ps[i].ri == p.ri && S.ps[i].ci == p.ci) ||p.ri==0||p.ri==h-1||p.ci==0||p.ci==w-1)
		{
			return false;
		}
	}
	return true;
}
void GenerateFood(food& f, int h, int w, snake& S)
{
	do {
		f.fp.ri = rand() % h;
		f.fp.ci = rand() % w;
	} while (!isLegalCoordinate(f.fp,h,w, S));
	f.isAlive = true;
	f.score = 1;

}



void init(snake &S,food &f,int height,int width)
{
	S.ps = new position[3];
	S.ps[0].ri = height / 2;
	S.ps[0].ci = width / 2;

	S.ps[1].ri = height / 2;
	S.ps[1].ci = width / 2-1;

	S.ps[2].ri = height / 2;
	S.ps[2].ci = width / 2-2;

	S.size = 3;
	S.score = 0;

	S.sym = -37;
	S.pName = "Mr. Snake";
	S.dir = RIGHT;
	S.RightKey = 77;
	S.LeftKey = 75;
	S.UpKey = 72;
	S.DownKey = 80;
	GenerateFood(f, height, width, S);
	f.sym = 3;
}


void init2(snake& S, food& f, int height, int width)
{
	S.ps = new position[3];
	S.ps[0].ri = height / 4;
	S.ps[0].ci = width / 4;

	S.ps[1].ri = height / 4;
	S.ps[1].ci = width / 4 - 1;

	S.ps[2].ri = height / 4;
	S.ps[2].ci = width / 4 - 2;

	S.size = 3;
	S.score = 0;

	S.sym = '>';
	gotoRowCol(20, 100);
	//cout << "name of 2 p:" << endl;
	S.pName="MR. chota snake";
	S.dir = RIGHT;
	S.DRightKey = 100;
	S.ALeftKey = 97;
	S.WUpKey = 119;
	S.SDownKey = 115;
	GenerateFood(f, height, width, S);
	f.sym = 3;
}


void init3(snake& S, food& f, int height, int width)
{
	S.ps = new position[3];
	S.ps[0].ri = height / 3;
	S.ps[0].ci = width / 3;

	S.ps[1].ri = height / 3;
	S.ps[1].ci = width / 3 - 1;

	S.ps[2].ri = height / 3;
	S.ps[2].ci = width / 3 - 2;

	S.size = 3;
	S.score = 0;

	S.sym = '~';
	gotoRowCol(24, 100);
	
	S.pName = "Mr. chota snake 3";
	S.dir = RIGHT;
	S.LRightKey = 108;
	S.JLeftKey = 106;
	S.IUpKey = 105;
	S.KDownKey = 107;
	GenerateFood(f, height, width, S);
	f.sym = 3;
}


void init4(snake& S, food& f, int height, int width)
{
	S.ps = new position[3];
	S.ps[0].ri = height / 5;
	S.ps[0].ci = width / 5;

	S.ps[1].ri = height / 5;
	S.ps[1].ci = width / 5 - 1;

	S.ps[2].ri = height / 5;
	S.ps[2].ci = width / 5 - 2;

	S.size = 3;
	S.score = 0;

	S.sym = '[';
	S.pName="MR. bara snake";
	S.dir = RIGHT;
	S.HRightKey = 104;
	S.FLeftKey = 102;
	S.TUpKey = 116;
	S.GDownKey = 103;
	GenerateFood(f, height, width, S);
	f.sym = 3;
}




void DisplayBoard(int height, int width, char sym)
{
	SetClr(9);
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (i == 0 || i == height -1 || j == 0 || j == width-1)
			{
				gotoRowCol(i, j);
				cout << sym;
			}
		}
		//cout << endl;
	}
	SetClr(15);
}
void DisplaySnake(const snake& S)
{
	SetClr(2);
	for (int i = 0; i < S.size; i++)
	{
		gotoRowCol(S.ps[i].ri, S.ps[i].ci);
		cout << S.sym;
	}
	SetClr(15);
}
void DisplayFood(food f)
{
	SetClr(12);
	gotoRowCol(f.fp.ri, f.fp.ci);
	cout << f.sym;
	SetClr(15);
}
void RemoveFood(food f)
{
	gotoRowCol(f.fp.ri, f.fp.ci);
	cout << ' ';
}
void RemoveSnake(const snake& S)
{
	for (int i = 0; i < S.size; i++)
	{
		gotoRowCol(S.ps[i].ri, S.ps[i].ci);
		cout <<' ';
	}
}
void MoveSnake(snake &S,int height , int width)
{
	for (int i = S.size - 1; i - 1 >= 0; i--)
	{
		S.ps[i] = S.ps[i - 1];
	}
	switch (S.dir)
	{
		case UP:
			S.ps[0].ri--;
			if (S.ps[0].ri == -1)
			{
				S.ps[0].ri = height - 1;
			}
			break;
		case DOWN:
			S.ps[0].ri++;
			if (S.ps[0].ri == height)
			{
				S.ps[0].ri = 0;
			}
			break;
		case RIGHT:
			S.ps[0].ci++;
			if (S.ps[0].ci == width)
			{
				S.ps[0].ci = 0;
			}
			break;
		case LEFT:
			S.ps[0].ci--;
			if (S.ps[0].ci == -1)
			{
				S.ps[0].ci = width - 1;
			}
			break;
	}
}

void ChangeDirection(snake& S, char key)
{
	//switch (ch)
	
	
	
	if (key == S.LeftKey)
	{
		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	}
	if (key == S.RightKey)
	{
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	}
	if (key == S.DownKey)
	{
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
	}
	if (key == S.UpKey)
	{
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	}
}

void ChangeDirection2(snake& S, char key)
{
	//switch (ch)



	if (key == S.ALeftKey)
	{
		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	}
	if (key == S.DRightKey)
	{
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	}
	if (key == S.SDownKey)
	{
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
	}
	if (key == S.WUpKey)
	{
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	}
}

void ChangeDirection3(snake& S, char key)
{
	//switch (ch)



	if (key == S.JLeftKey)
	{
		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	}
	if (key == S.LRightKey)
	{
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	}
	if (key == S.KDownKey)
	{
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
	}
	if (key == S.IUpKey)
	{
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	}
}

void ChangeDirection4(snake& S, char key)
{
	//switch (ch)



	if (key == S.FLeftKey)
	{
		if (S.dir != RIGHT)
		{
			S.dir = LEFT;
		}
	}
	if (key == S.HRightKey)
	{
		if (S.dir != LEFT)
		{
			S.dir = RIGHT;
		}
	}
	if (key == S.GDownKey)
	{
		if (S.dir != UP)
		{
			S.dir = DOWN;
		}
	}
	if (key == S.TUpKey)
	{
		if (S.dir != DOWN)
		{
			S.dir = UP;
		}
	}
}

bool IsFoodEaten(snake& S, food& f)
{
	return S.ps[0].ri == f.fp.ri && S.ps[0].ci == f.fp.ci;
}
void ExpandSnake(snake& S)
{
	position* HP=new position [S.size+1];

	for (int i = 0; i < S.size; i++)
	{
		HP[i] = S.ps[i];
	}
	HP[S.size] = S.ps[S.size - 1];
	S.size++;
	delete[]S.ps;
	S.ps = HP;
}
bool SnekRip(snake& S,int height, int width)
{
	if (S.ps[0].ri == 0 ||S.ps[0].ri==height-1 ||S.ps[0].ci==0|| S.ps[0].ci == width-1) 
	{
		return true;
	}
	return false;
}
bool suicide(snake& S)
{
	for (int i =1; i <S.size; i++)
	{
		if (S.ps[0].ri == S.ps[i].ri && S.ps[0].ci == S.ps[i].ci)
		{
			return true;
		}
	}
	return false;
}


int main()
{
	srand(time(0));
	sndPlaySound(TEXT("snake.wav"), SND_ASYNC);
	//char ch;
	int height=60, width =80;
	snake S[4];
	//food f;
	//init(S[0], f, height, width);
	//DisplayBoard(height, width, -37);
	//DisplayFood(f);
	//S[0].score = 0;
	//int t = time(0);
	int opt;
	cout << "enter 1 to play one player SNAKE GAME" << endl;
	cout << "enter 2 to play two players SNAKE GAME" << endl;
	cout << "enter 3 to play three players SNAKE GAME" << endl;
	cout << "enter 4 to play four players SNAKE GAME" << endl;
	cin >> opt;

	if (opt == 1)
	{
		system("cls");
		DisplayBoard(height, width, -37);
		char ch;
		food f;
		init(S[0], f, height, width);
		DisplayFood(f);
		gotoRowCol(10, 100);
		cout << "score is " << endl;
		gotoRowCol(14, 100);
		cout << "time is " << endl;
		float t = 0;
		bool gameover = false;
		bool killS0 = false;
		while (gameover!=true)
		{
			gotoRowCol(12, 100);
			cout << S[0].score;
			gotoRowCol(16, 100);
			cout << t << endl;
			//cout << played;
			//int t = time(0);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					ChangeDirection(S[0], ch);
				}
			}
			if (killS0 != true) {
				DisplaySnake(S[0]);
			}
			Sleep(100);
			RemoveSnake(S[0]);
			MoveSnake(S[0], height, width);
			if (IsFoodEaten(S[0], f))
			{
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				ExpandSnake(S[0]);
				S[0].score++;
				t = 0;
			}
			if (t == 100)
			{
				IsFoodEaten(S[0], f) == true;
				RemoveFood(f);
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				t = 0;
			}
			if (SnekRip(S[0], height, width))
			{
				killS0 = true;
				//gameover += 1;
			}
			if (suicide(S[0]) == true)
			{
				killS0 = true;
				//gameover += 1;
			}
			if (killS0 == true)
			{
				system("cls");
				gotoRowCol(height / 2, width / 2);
				cout << "game over" << endl;
			}
			t += 1;
		}
	}
	if (opt == 2)
	{
		system("cls");
		DisplayBoard(height, width, -37);
		char ch;
		food f;
		init(S[0], f, height, width);
		init2(S[1], f, height, width);
		DisplayFood(f);
		gotoRowCol(18, 90);
		cout << "p1 " <<setw(2)<<"p2" << endl;
		gotoRowCol(20, 90);
		cout << S[0].score << setw(5) << S[1].score;
		gotoRowCol(14, 90);
		cout << "time is " << endl;
		float k = 0;
		bool gameover = false;
		bool killS0 = false;
		bool killS1 = false;
		while (gameover!=true)
		{
			gotoRowCol(16, 90);
			cout << k << endl;
			//cout << played;
			//int t = time(0);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					ChangeDirection(S[0], ch);
				}
				if (ch == 119 || ch == 100 || ch == 97 || ch == 115)
				{
					//ch = _getch();
					ChangeDirection2(S[1], ch);
				}
			}
			if (killS0 != true) {
				DisplaySnake(S[0]);
			}
			if (killS1 != true) {
				DisplaySnake(S[1]);
			}
			Sleep(100);
			RemoveSnake(S[0]);
			RemoveSnake(S[1]);
			MoveSnake(S[0], height, width);
			MoveSnake(S[1], height, width);
			if (IsFoodEaten(S[0], f))
			{
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				ExpandSnake(S[0]);
				S[0].score++;
				k = 0;
			}
			if (IsFoodEaten(S[1], f))
			{
				GenerateFood(f, height, width, S[1]);
				DisplayFood(f);
				ExpandSnake(S[1]);
				S[1].score++;
				k = 0;
			}
			if (k == 100)
			{
				IsFoodEaten(S[0], f) == true;
				RemoveFood(f);
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				k = 0;
			}
			if (SnekRip(S[0], height, width))
			{
				killS0 = true;
				//gameover +=1;
			}
			if (suicide(S[0]) == true)
			{
				killS0 = true;
				//gameover += 1;
			}
			if (SnekRip(S[1], height, width))
			{
				killS1 = true;
				//gameover += 1;
			}
			if (suicide(S[1]) == true)
			{
				killS1 = true;
				//gameover += 1;
			}
			if (killS0==true && killS1==true)
			{
				system("cls");
				gotoRowCol(height / 2, width / 2);
				cout << "game over" << endl;
			}
			k += 1;
		}
	}
	if (opt == 3)
	{
		system("cls");
		DisplayBoard(height, width, -37);
		char ch;
		food f;
		init(S[0], f, height, width);
		init2(S[1], f, height, width);
		init3(S[2], f, height, width);
		DisplayFood(f);
		gotoRowCol(18, 90);
		cout << "p1 " << setw(2) << "p2" <<setw(2)<< "p3" << endl;
		gotoRowCol(20, 90);
		cout << S[0].score << setw(5) << S[1].score << setw(5) << S[2].score;
		gotoRowCol(14, 90);
		cout << "time is " << endl;
		bool killS0 = false;
		bool killS1 = false;
		bool killS2 = false;
		float q = 0;
		bool gameover = false;
		while (gameover!=true)
		{
			gotoRowCol(12, 100);
			cout << S[0].score;
			gotoRowCol(16, 100);
			cout << q << endl;
			//cout << played;
			//int t = time(0);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					ChangeDirection(S[0], ch);
				}
				if (ch == 119 || ch == 100 || ch == 97 || ch == 115)
				{
					//ch = _getch();
					ChangeDirection2(S[1], ch);
				}
				if (ch == 108 || ch == 106 || ch == 105 || ch == 107)
				{
					//ch = _getch();
					ChangeDirection3(S[2], ch);
				}
			}
			if (killS0 != true) {
				DisplaySnake(S[0]);
			}
			if (killS1 != true) {
				DisplaySnake(S[1]);
			}
			if (killS2 != true) {
				DisplaySnake(S[2]);
			}
			Sleep(100);
			RemoveSnake(S[0]);
			RemoveSnake(S[1]);
			RemoveSnake(S[2]);
			MoveSnake(S[0], height, width);
			MoveSnake(S[1], height, width);
			MoveSnake(S[2], height, width);
			if (IsFoodEaten(S[0], f))
			{
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				ExpandSnake(S[0]);
				S[0].score++;
				q = 0;
			}
			if (IsFoodEaten(S[1], f))
			{
				GenerateFood(f, height, width, S[1]);
				DisplayFood(f);
				ExpandSnake(S[1]);
				S[1].score++;
				q = 0;
			}
			if (IsFoodEaten(S[2], f))
			{
				GenerateFood(f, height, width, S[2]);
				DisplayFood(f);
				ExpandSnake(S[2]);
				S[2].score++;
				q = 0;
			}
			if (q == 100)
			{
				IsFoodEaten(S[0], f) == true;
				RemoveFood(f);
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				q = 0;
			}
			if (SnekRip(S[0], height, width))
			{
				killS0 = true;
				//gameover +=1;
			}
			if (suicide(S[0]) == true)
			{
				killS0 = true;
				//gameover += 1;
			}
			if (SnekRip(S[1], height, width))
			{
				killS1 = true;
				//gameover +=1;
			}
			if (suicide(S[1]) == true)
			{
				killS1 = true;
				//gameover += 1;
			}
			if (SnekRip(S[2], height, width))
			{
				killS2 = true;
				//gameover +=1;
			}
			if (suicide(S[2]) == true)
			{
				killS2 = true;
				//gameover += 1;
			}
			if (killS0 ==true && killS1==true && killS2==true)
			{
				system("cls");
				gotoRowCol(height / 2, width / 2);
				cout << "game over" << endl;
			}
			q += 1;
		}
	}
	if (opt == 4)
	{
		system("cls");
		DisplayBoard(height, width, -37);
		char ch;
		food f;
		init(S[0], f, height, width);
		init2(S[1], f, height, width);
		init3(S[2], f, height, width);
		init4(S[3], f, height, width);
		DisplayFood(f);
		gotoRowCol(14, 90);
		cout << "time is " << endl;
		float e = 0;
		bool gameover = false;
		bool killS0 = false;
		bool killS1 = false;
		bool killS2 = false;
		bool killS3 = false;
		while (gameover!=true)
		{
			gotoRowCol(18, 90);
			cout << "p1 " << setw(2) << "p2" <<setw(2)<< "p3" << setw(2)<<"p4" << endl;
			gotoRowCol(20, 90);
			cout << S[0].score << setw(5) << S[1].score << setw(5) << S[2].score << setw(5) << S[3].score << endl;;
			gotoRowCol(16, 100);
			cout << e << endl;
			//cout << played;
			//int t = time(0);
			if (_kbhit())
			{
				ch = _getch();
				if (ch == -32)
				{
					ch = _getch();
					ChangeDirection(S[0], ch);
				}
				if (ch == 119 || ch == 100 || ch == 97 || ch == 115)
				{
					//ch = _getch();
					ChangeDirection2(S[1], ch);
				}
				if (ch == 108 || ch == 106 || ch == 105 || ch == 107)
				{
					//ch = _getch();
					ChangeDirection3(S[2], ch);
				}
				if (ch == 104 || ch == 102 || ch == 116 || ch == 103)
				{
					//ch = _getch();
					ChangeDirection4(S[3], ch);
				}
			}
			if (killS0 != true) {
				DisplaySnake(S[0]);
			}
			if (killS1 != true) {
				DisplaySnake(S[1]);
			}
			if (killS2 != true) {
				DisplaySnake(S[2]);
			}
			if (killS3 != true) {
				DisplaySnake(S[3]);
			}
			Sleep(100);
			RemoveSnake(S[0]);
			RemoveSnake(S[1]);
			RemoveSnake(S[2]);
			RemoveSnake(S[3]);
			MoveSnake(S[0], height, width);
			MoveSnake(S[1], height, width);
			MoveSnake(S[2], height, width);
			MoveSnake(S[3], height, width);
			if (IsFoodEaten(S[0], f))
			{
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				ExpandSnake(S[0]);
				S[0].score++;
				e = 0;
			}
			if (IsFoodEaten(S[1], f))
			{
				GenerateFood(f, height, width, S[1]);
				DisplayFood(f);
				ExpandSnake(S[1]);
				S[1].score++;
				e = 0;
			}
			if (IsFoodEaten(S[2], f))
			{
				GenerateFood(f, height, width, S[2]);
				DisplayFood(f);
				ExpandSnake(S[2]);
				S[2].score++;
				e = 0;
			}
			if (IsFoodEaten(S[3], f))
			{
				GenerateFood(f, height, width, S[3]);
				DisplayFood(f);
				ExpandSnake(S[3]);
				S[3].score++;
				e = 0;
			}
			if (e == 100)
			{
				IsFoodEaten(S[0], f) == true;
				RemoveFood(f);
				GenerateFood(f, height, width, S[0]);
				DisplayFood(f);
				e = 0;
			}
			if (SnekRip(S[0], height, width))
			{
				/*for (int i = 0; i < S[0].size; i++)
				{
					S[0].ps[i].ri = ' ';
					S[0].ps[i].ci = ' ';
				}*/
				killS0 = true;
				//gameover+=1;
			}
			if (suicide(S[0]) == true)
			{
				killS0 = true;
				//gameover += 1;
			}
			if (SnekRip(S[1], height, width))
			{
				killS1 = true;
				//gameover += 1;
			}
			if (suicide(S[1]) == true)
			{
				killS1 = true;
				//gameover += 1;
			}
			if (SnekRip(S[2], height, width))
			{
				killS2 = true;
				//gameover += 1;
			}
			if (suicide(S[2]) == true)
			{
				killS2 = true;
				//gameover += 1;
			}
			if (SnekRip(S[3], height, width))
			{
				killS3 = true;
				//gameover += 1;
			}
			if (suicide(S[3]) == true)
			{
				killS3 = true;
				//gameover += 1;
			}
			if (killS0==true && killS1==true && killS2==true && killS3==true)
			{
				system("cls");
				gotoRowCol(height / 2, width / 2);
				cout << "game over " << endl;
			}
			e += 1;
		}
	}

	_getch();
	
	return 0;
}