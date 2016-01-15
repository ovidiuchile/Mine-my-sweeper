#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <math.h>
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
void encrypt(int n, char s[]) //not used
{
    srand(time(NULL));
    for(int i=0;i<64;i++)
    {
        int x=rand()%62;
        if(x<=9)
            s[i]=char(x+48);
        else
            if(x<=35)
                s[i]=char(x+55);
            else
                s[i]=char(x+61);
    }
    s[64]='\0';
    s[39]=n/100+'0'+23;
    s[40]=(n/10)%10+'0'+54;
    s[41]=n%10+'0'+17;
}
void decrypt(int &n, char s[]) // not used
{
    int ok=1;
    if(s[41]<65||s[41]>74)
        ok=0;
    if(s[40]<102||s[40]>111)
        ok=0;
    if(s[39]<71||s[39]>80)
        ok=0;
    if(ok==0)
        strcpy(s,"0");
    else
        n=(s[41]-17-'0')+(s[40]-54-'0')*10+(s[39]-23-'0')*100;
}
void resetMyFile()  //not used
{
    int n=999;
    char s[400];
    encrypt(n,s);
    fstream f;
    f.open("score", fstream::out);
    f<<s;
    encrypt(n,s);
    f<<s;
    encrypt(n,s);
    f<<s;
    f.close();
}
void setNullScoreIfNeeded() // not used
{
    fstream f;
    f.open("score", fstream::in);
    char s[400],s1[400];
    f.getline(s,400);
    f.close();
    int n;
    if(strlen(s)!=192)
    {
        cout<<strlen(s);
        resetMyFile();
        return;
    }
    strcpy(s1,s);
    s1[64]='\0';
    decrypt(n,s1);
    if(strcmp(s1,"0")==0)
    {
        resetMyFile();
        return;
    }
    strcpy(s1,s);
    strcpy(s1,s1+64);
    s1[64]='\0';
    decrypt(n,s1);
    if(strcmp(s1,"0")==0)
    {
        resetMyFile();
        return;
    }
    strcpy(s1,s);
    strcpy(s1,s1+128);
    s1[64]='\0';
    decrypt(n,s1);
    if(strcmp(s1,"0")==0)
    {
        resetMyFile();
        return;
    }
}
void biggerPrintStartupScreen()  //not used
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
