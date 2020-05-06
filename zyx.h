//Idea by Kinshuk Vasisht

//Windows part created by Kinshuk Vasisht
//Linux part created by FlamingArrow
#include<string.h>
#ifndef CCONIO_H_INCLUDED
#define CCONIO_H_INCLUDED

// Note : This is a header. Save inside a .h
//        or .hpp file to use.

/// Library to redeclare conio.h 's functions and add new manipulators etc for the same.
/// Uses xcode and WinAPI functions inside wrapper functions, so it becomes multi-platform.

/**

>>> Current Supported Functions -
    =============================

  1) getch()        -  Accepts a single key from the console.
  2) ungetch()      -  Resends key back to keyboard buffer.
  3) getpass()      -  Accepts a Password from the console.
  4) getche()       -  Reads a key from the console and prints it on the terminal.
  5) putch()        -  Prints a character directly to the console.
  6) textcolor()    -  Sets the text foreground color.
  7) textbackground -  Sets the text background color.
  8) clrscr()       -  Clears the screen using Terminal API Calls.
  9) gotoxy()       -  Sets the cursor at the position specified by x and y.
 10) kbhit()        -  Reads a single key directly from the keyboard.
 11) wherex()       -  Returns Current Horizontal Position.
 12) wherey()       -  Returns Current Vertical Position.
 13) cgets()        -  Reads a char* string from the console.
 14) cputs()        -
 15) clreol()       -

>>> New Added Functions -
    =====================

  1) kbvhit()    - Reads a Virtual Key from the Keyboard.
  2) csgets()    - Reads a C++03 string from the console directly.

Only basic functions work in Lunux for now ;(
**/

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

// char getch()
// {
//     if(bufkey!=0&&mark) 
//     {mark = false; return bufkey;}
//     INPUT_RECORD IR; DWORD evs; CHAR ch;
//     while(true)
//     {
//         WINBOOL a = ReadConsoleInput(GetStdHandle(STD_INPUT_HANDLE), &IR, 1, &evs);
//         if(not a) break;
//         if (IR.EventType == KEY_EVENT && IR.Event.KeyEvent.wVirtualKeyCode != VK_SHIFT && IR.Event.KeyEvent.bKeyDown
//             && IR.Event.KeyEvent.wVirtualKeyCode != VK_MENU && IR.Event.KeyEvent.wVirtualKeyCode != VK_CONTROL)
//         {
//             ch = IR.Event.KeyEvent.uChar.AsciiChar;
//             mark = false; bufkey = ch;
//             return ch;
//         }
//         else if(IR.EventType == MOUSE_EVENT)
//         {
//             continue;
//         }
//     }
//     mark = false; bufkey = EOF;
//     return EOF;
// }

// int ungetch(char ch)
// {
//     if(bufkey==0) return EOF;
//     bufkey = ch;
//     mark = true;
//     return ch;
// }

// char* getpass(const char* prompt)
// {
//     const int MAX = 128; char * pwd = new char[MAX];
//     char BACKSPACE='\b', RETURN='\r'; unsigned char ch = 0;
//     DWORD mode; GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE),&mode); DWORD ev; size_t i = 0;
//     HANDLE in=GetStdHandle(STD_INPUT_HANDLE);
//     SetConsoleMode(in, mode & ~(ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT));
//     cout<<prompt;
//     while(ReadConsoleA(in,&ch,1,&ev,NULL) && ch != RETURN)
//     {
//        if(ch==BACKSPACE)
//        {
//           if(strlen(pwd)!=0)
//           {
//               cout <<"\b \b";
//               i--;
//           }
//        }
//        else
//        {
//           pwd[i]=ch; cout <<'*'; i++;
//        }
//     }
//     SetConsoleMode(in, mode); pwd[i]='\0';
//     return pwd;
// }

// string getpass(string prompt)
// {
//     char BACKSPACE='\b', RETURN='\r';
//     string pw=""; unsigned char ch = 0;
//     HANDLE in=GetStdHandle(STD_INPUT_HANDLE);
//     DWORD mode , ev; GetConsoleMode(in,&mode);
//     SetConsoleMode(in, mode & ~(ENABLE_ECHO_INPUT|ENABLE_LINE_INPUT));
//     cout<<prompt;
//     while(ReadConsoleA(in,&ch,1,&ev,NULL) && ch != RETURN)
//     {
//        if(ch==BACKSPACE)
//        {
//           if(pw.length()!=0)
//           {
//               cout <<"\b \b";
//               pw.resize(pw.length()-1);
//           }
//        }
//        else
//        {
//           pw += ch; cout <<'*';
//        }
//     }
//     SetConsoleMode(in, mode);
//     return pw;
// }

// char getche()
// {
//     char c = getch(); CONSOLE_SCREEN_BUFFER_INFO csbi; DWORD ev;
//     GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
//     WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&FCOL,1,csbi.dwCursorPosition,&ev); ev = 0;
//     WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),&c,1,csbi.dwCursorPosition,&ev); return c;
// }
int putch(int ch)
{
    CONSOLE_SCREEN_BUFFER_INFO csbi; DWORD ev;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    WriteConsoleOutputAttribute(GetStdHandle(STD_OUTPUT_HANDLE),&FCOL,1,csbi.dwCursorPosition,&ev); ev = 0;
    if(WriteConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE),reinterpret_cast<char*>(&ch),1,csbi.dwCursorPosition,&ev))
        return ch;
    return EOF;
}

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

int kbhit()
{
    INPUT_RECORD IR; DWORD evs; CHAR ch;
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    while(true)
    {
        WINBOOL a = ReadConsoleInput(in, &IR, 1, &evs);
        if(not a) break;
        if (IR.EventType == KEY_EVENT && IR.Event.KeyEvent.bKeyDown)
        {
            ch = IR.Event.KeyEvent.uChar.AsciiChar;
            return static_cast<int>(ch);
        }
        else if(IR.EventType == MOUSE_EVENT)
        {
            continue;
        }
    }
    return EOF;
}

int kbvhit()
{
    INPUT_RECORD IR; DWORD evs;
    HANDLE in = GetStdHandle(STD_INPUT_HANDLE);
    while(true)
    {
        WINBOOL a = ReadConsoleInput(in, &IR, 1, &evs);
        if(not a) break;
        if (IR.EventType == KEY_EVENT && IR.Event.KeyEvent.bKeyDown)
        {
            return static_cast<int>(IR.Event.KeyEvent.wVirtualKeyCode);
        }
        else if(IR.EventType == MOUSE_EVENT)
        {
            continue;
        }
    }
    return EOF;
}

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    return csbi.dwCursorPosition.X;
}

int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&csbi);
    return csbi.dwCursorPosition.Y;
}

char* cgets(char* buf)
{
    char* p = new char[static_cast<int>(buf[0])];
    INPUT_RECORD IR; DWORD evs; CHAR ch; int i=0;
    while(true)
    {
        WINBOOL a = ReadConsoleInput(STDIN, &IR, 1, &evs);
        CONSOLE_SCREEN_BUFFER_INFO csbi; GetConsoleScreenBufferInfo(STDOUT,&csbi);
        if(not a || i>=(buf[0]-3)) {i++; break;}
        if (IR.EventType == KEY_EVENT && IR.Event.KeyEvent.bKeyDown)
        {
            COORD cpt = {SHORT(csbi.dwCursorPosition.X+i),SHORT(csbi.dwCursorPosition.Y)};
            if(IR.Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {i++; break;}
            if(IR.Event.KeyEvent.wVirtualKeyCode == VK_BACK && i>0)
            {
                i--; DWORD ev; COORD cpt2 = {SHORT(csbi.dwCursorPosition.X+i),SHORT(csbi.dwCursorPosition.Y)};
                WriteConsoleOutputAttribute(STDOUT,&csbi.wAttributes,1,cpt2,&ev); ev = 0; char cc = ' ';
                WriteConsoleOutputCharacter(STDOUT,reinterpret_cast<char*>(&cc),1,cpt2,&ev); continue;
            }
            ch = IR.Event.KeyEvent.uChar.AsciiChar; DWORD ev;
            WriteConsoleOutputAttribute(STDOUT,&FCOL,1,cpt,&ev); ev = 0;
            WriteConsoleOutputCharacter(STDOUT,reinterpret_cast<char*>(&ch),1,cpt,&ev);
            //SetConsoleCursorPosition(STDOUT,cpt);
            p[i] = ch; buf[i+2] = ch; i++;
        }
    }
    buf[1]=char(i-1); p[i] = '\0'; buf[i+2] = '\0';
    return p;
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

#else
/// Linux Version

#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/select.h>

static void terminal_lnbuf(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ICANON;
   else newt.c_lflag |= ICANON;
   tcsetattr(0, TCSANOW, &newt);
}
 
static void terminal_echo(int yn) {
   struct termios oldt, newt;
   tcgetattr(0, &oldt);
   newt = oldt;
   if (!yn) newt.c_lflag &= ~ECHO;
   else newt.c_lflag |= ECHO;
   tcsetattr(0, TCSANOW, &newt);
}
     
static void gotoxy(int x, int y) { std::cout << "\x1B[%d;%df" << y << x; }

static void _gotoxy(int x,int y) {gotoxy(x,y);}
     
static void clrscr() { system("clear"); }

static void _clrscr() {clrscr();}
     
static int getch() {
   register int ch;
   terminal_lnbuf(0);
   terminal_echo(0);
   ch = getchar();
   terminal_lnbuf(1);
   terminal_echo(1);
   return ch;
}

static int _getch() {return getch();}
     
static int getche() {
   register int ch;
   terminal_lnbuf(0);
   ch = getchar();
   terminal_lnbuf(1);
   return ch;
}

static int _getche() {return getche();}

static int kbhit() {
   register int ret;
   fd_set fds;
   terminal_lnbuf(0);
   terminal_echo(0);
   struct timeval tv;
   tv.tv_sec = 0;
   tv.tv_usec = 0;
   FD_ZERO(&fds);
   FD_SET(0, &fds);
   select(1, &fds, 0, 0, &tv);
   ret = FD_ISSET(0, &fds);
   terminal_lnbuf(1);
   terminal_echo(1);
   return ret;
}

static int _kbhit() {return kbhit();}

#endif
#endif // CCONIO_H_INCLUDED
