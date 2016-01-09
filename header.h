#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
using namespace std;
int mineMatrix[100][100],shownMatrixBehind[100][100],shownMatrixBehind2[100][100];
int numberOfUncoveredSafePlaces,numberOfRemainingBombs,ok,rules,matchLost;
bool playAgain;
char shownMatrix[100][100];
HANDLE h;
COORD p;
void SetCursorPosition(int x, int y)
{
    h=GetStdHandle(STD_OUTPUT_HANDLE);
	p.X=y;
	p.Y=x;
	SetConsoleCursorPosition(h, p);
}
void setColor(int c)
{
    /*
    0   black
    1   blue
    2   green
    3   teal
    4   red
    5   pink
    6   yellow
    7   light gray
    8   gray
    9   bright blue
    10  bright green
    11  bright teal
    12  bright red
    13  bright pink
    14  bright yellow
    15  bright white
    */
	HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO cons;
	GetConsoleScreenBufferInfo(h, &cons);
	SetConsoleTextAttribute(h,(cons.wAttributes&0xFFF0)|(WORD)c);
}
void printStartupScreen()
{
    cout<<"             MINESWEEPER\n";
    setColor(12);
    cout<<"                ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"                \n";
    cout<<"     \\ \\ \\      ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"      / / /     \n";
    cout<<"      \\ \\ \\     ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"     / / /      \n";
    cout<<"       \\ \\ \\    ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"    / / /       \n";
    cout<<"        \\ \\ \\   ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"   / / /        \n";
    cout<<"         \\ \\ \\  ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"  / / /         \n";
    cout<<"          \\ \\ \\ ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" / / /          \n";
    cout<<"           \\ \\ \\";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"/ / /           \n";
    cout<<"            \\ \\ ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" / /             \n";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    setColor(12);
    cout<<"            / / ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" \\ \\                      \n";
    cout<<"           / / /";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"\\ \\ \\                    \n";
    cout<<"          / / / ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" \\ \\ \\                   \n";
    cout<<"         / / /  ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"  \\ \\ \\                  \n";
    cout<<"        / / /   ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"   \\ \\ \\                 \n";
    cout<<"       / / /    ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"    \\ \\ \\                \n";
    cout<<"      / / /     ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"     \\ \\ \\               \n";
    cout<<"     / / /      ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"      \\ \\ \\              \n";
    cout<<"                ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"\n\nPress any key to continue...\n";
    kbhit();
    getch();
}
void biggerPrintStartupScreen()
{
    cout<<"             MINESWEEPER\n";
    cout<<" \\ \\ \\          ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"          / / /\n";
    cout<<"  \\ \\ \\         ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"         / / / \n";
    cout<<"   \\ \\ \\        ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"        / / /  \n";
    cout<<"    \\ \\ \\       ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"       / / /   \n";
    cout<<"     \\ \\ \\      ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"      / / /     \n";
    cout<<"      \\ \\ \\     ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"     / / /      \n";
    cout<<"       \\ \\ \\    ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"    / / /       \n";
    cout<<"        \\ \\ \\   ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"   / / /        \n";
    cout<<"         \\ \\ \\  ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"  / / /         \n";
    cout<<"          \\ \\ \\ ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" / / /          \n";
    cout<<"           \\ \\ \\";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"/ / /           \n";
    cout<<"            \\ \\ ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" / /             \n";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196);
    setColor(12);
    cout<<"+ + +";
    setColor(0);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<char(196)<<char(196)<<char(196)<<char(196);
    cout<<char(196)<<'\n';
    setColor(12);
    cout<<"            / / ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" \\ \\                      \n";
    cout<<"           / / /";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"\\ \\ \\                    \n";
    cout<<"          / / / ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<" \\ \\ \\                   \n";
    cout<<"         / / /  ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"  \\ \\ \\                  \n";
    cout<<"        / / /   ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"   \\ \\ \\                 \n";
    cout<<"       / / /    ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"    \\ \\ \\                \n";
    cout<<"      / / /     ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"     \\ \\ \\               \n";
    cout<<"     / / /      ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"      \\ \\ \\              \n";
    cout<<"    / / /       ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"       \\ \\ \\            \n";
    cout<<"   / / /        ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"        \\ \\ \\           \n";
    cout<<"  / / /         ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"         \\ \\ \\          \n";
    cout<<" / / /          ";
    setColor(0);
    cout<<"| | |";
    setColor(12);
    cout<<"          \\ \\ \\         \n";
    cout<<"\n\nPress any key to continue...\n";
    kbhit();
    getch();
}
