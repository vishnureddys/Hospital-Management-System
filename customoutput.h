#ifndef CCONIO_H_INCLUDED
#define CCONIO_H_INCLUDED
#include<string.h>
#include <iostream>
#include <conio.h>

using namespace std;

enum
{
    BLACK = 0, BLUE, GREEN, CYAN, RED, 
    MAGENTA, BROWN, LIGHTGRAY, DARKGRAY,
    LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, 
    LIGHTRED, LIGHTMAGENTA, YELLOW, WHITE
};

#if defined(WIN32) || defined(__WIN32) || defined(__WIN32__)
/// Windows Version
#include <windows.h>


char bufkey=0; bool mark = 0;
WORD CCOL = LIGHTGRAY;
WORD BCOL = BLACK;
WORD FCOL = LIGHTGRAY;

HANDLE STDOUT = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE STDIN  = GetStdHandle(STD_INPUT_HANDLE );

void textcolor(WORD color)
{
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
    CCOL = color;
    FCOL = (16*BCOL)+CCOL;
}

void textbackground(WORD color)
{
    //SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),(16*(color))+CCOL);
    BCOL = color;
    FCOL = (16*(BCOL))+CCOL;
}

void clrscr()
{
    system("cls");
}

void gotoxy(int x, int y)
{
    COORD CONSOLECOORD; CONSOLECOORD.X=x; CONSOLECOORD.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),CONSOLECOORD);
}

void clreol(void)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(STDOUT,&csbi);
    string data="";
    for(int i=0;i<csbi.dwMaximumWindowSize.X;i++)
        data+=' ';
    COORD c = {0,SHORT(csbi.dwCursorPosition.Y)};
    DWORD ev = 0;
    //SetConsoleTextAttribute(STDOUT,col);
    WriteConsoleOutputAttribute(STDOUT,&FCOL,csbi.dwSize.X,c,&ev); ev=0;
    WriteConsoleOutputCharacter(STDOUT,data.c_str(),csbi.dwMaximumWindowSize.X,c,&ev);
    gotoxy(0,csbi.dwCursorPosition.Y);
}
#endif
#endif // CCONIO_H_INCLUDED