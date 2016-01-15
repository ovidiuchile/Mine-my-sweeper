#include "header.h"
#include "functions.h"
int main()
{
    SetFileAttributes("score", FILE_ATTRIBUTE_HIDDEN);
    system("COLOR FC"); //set the background white and text color red
    int numberOfLines,numberOfColumns,numberOfBombs;
    char difficulty[100];
    printStartupScreen();
beginning:
    while (1)
    {
        system("cls"); //clear the screen
        setColor(12); //set the text color red
        cout<<"             MINESWEEPER\n\n";
        _sleep(800);
        printRules();
        cout<<"\nReady?\n";
        _sleep(800);
        chooseDifficulty(numberOfLines,numberOfColumns,numberOfBombs,difficulty);
        createShownMatrix(numberOfLines,numberOfColumns,numberOfBombs);
        system("cls");
        play(numberOfLines,numberOfColumns,numberOfBombs,difficulty);
        if(playAgain==true)
        {
            system("cls");
            resetFreeVariables();
            goto beginning;
        }
        else break;
    }
    return 0;
}
