#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <ncurses/curses.h>
#include <iostream>
using namespace std;

int maxX,maxY;
bool game = true;
char arah ='d';
int x,y;
int score = 0;
int tailLength = 1;
int tailX[100], tailY[100];
int fruitX,fruitY;

void Draw(){
	clear();
	WINDOW *win = newwin(maxY, maxX, 0, 0);
	refresh();
	box(win,0,0);
	wrefresh(win);
	mvprintw(y,x,"O");
	mvprintw(fruitY,fruitX,"#");
	
	for (int i = 0; i < tailLength; i++) {
        mvprintw(tailY[i], tailX[i], "o");
    }
    
	refresh();
	Sleep(100);
}

void Console(){
	if(kbhit()){
		switch(getch()){
			case 'a' : if(arah!='d')arah = 'a'; break;
			case 'd' : if(arah!='a')arah = 'd'; break;
			case 'w' : if(arah!='s')arah = 'w'; break;
			case 's' : if(arah!='w')arah = 's'; break;
			case 'q' : game = false; break;
		}	
	}
}

void Algorithm(){
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < tailLength; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
	if (arah == 'w') {
        y--;
    }
    if (arah == 's') {
        y++;
    }
    if (arah == 'a') {
        x--;
    }
    if (arah == 'd') {
        x++;
    }
    if (fruitX == x &&fruitY == y){
    	score++;
    	fruitX = rand()%maxX;
    	fruitY = rand()%maxY;
    	tailLength++;
	}
    for (int i = 0; i < tailLength; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            game = false;
        }
    }
    
    if (x <= 0 || x >= maxX || y <= 0 || y >= maxY) {
        game = false;
    }
}

int main(){
	initscr();
	noecho();
	curs_set(0);
	getmaxyx(stdscr,maxY,maxX);

	x = maxX/2;
	y = maxY/2;
	fruitX = rand()%maxX;
	fruitY = rand()%maxY;
	
	do {
		Draw();
		Console();
		Algorithm();
	}while(game);
	
	clear();
    mvprintw(maxY/2,maxX/2,"Score anda adalah %d",score);
    
	refresh();
	getch();
	endwin();
	return 0;
}
