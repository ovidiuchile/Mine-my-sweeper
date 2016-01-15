int getSumOfNeighbors(int numberOfLines, int numberOfColumns, int x, int y)
{
    int nr=0;
    if(x>0)
        nr+=mineMatrix[x-1][y-1]+mineMatrix[x-1][y]+mineMatrix[x-1][y+1];
    if(x<numberOfLines-1)
        nr+=mineMatrix[x+1][y-1]+mineMatrix[x+1][y]+mineMatrix[x+1][y+1];
    if(y>0)
        nr+=mineMatrix[x-1][y-1]+mineMatrix[x][y-1]+mineMatrix[x+1][y-1];
    if(y<numberOfColumns)
        nr+=mineMatrix[x-1][y+1]+mineMatrix[x][y+1]+mineMatrix[x+1][y+1];
    if(x>0&&y>0)
        nr-=mineMatrix[x-1][y-1];
    if(x<numberOfLines&&y<numberOfColumns)
        nr-=mineMatrix[x+1][y+1];
    if(x<numberOfLines&&y>0)
        nr-=mineMatrix[x+1][y-1];
    if(x>0&&y<numberOfColumns)
        nr-=mineMatrix[x-1][y+1];
    return nr;
}
int getSumOfNeighborsOnShownMatrix(int numberOfLines, int numberOfColumns, int x, int y)
{
    shownMatrixBehind2[x][y]=1;
    int nr=0;
    if(x>1&&y>1)                                    if(shownMatrix[x-2][y-2]==char(207)) nr++;
    if(x>1)                                         if(shownMatrix[x-2][y]==char(207)) nr++;
    if(x>1&&y<2*numberOfColumns-1)                  if(shownMatrix[x-2][y+2]==char(207)) nr++;    //1 2 3
    if(y>1)                                         if(shownMatrix[x][y-2]==char(207)) nr++;      //4   5
    if(y<2*numberOfColumns-1)                       if(shownMatrix[x][y+2]==char(207)) nr++;      //6 7 8
    if(x<2*numberOfLines-1&&y>1)                    if(shownMatrix[x+2][y-2]==char(207)) nr++;
    if(x<2*numberOfLines-1)                         if(shownMatrix[x+2][y]==char(207)) nr++;
    if(x<2*numberOfLines-1&&y<2*numberOfColumns-1)  if(shownMatrix[x+2][y+2]==char(207)) nr++;
    return nr;
}
void uncoverSquare(int numberOfLines, int numberOfColumns, int x, int y, char &c)
{
    if(shownMatrix[x][y]==' '||shownMatrix[x][y]==char(207))
        return;
    if(isdigit(shownMatrix[x][y])&&c==' ')
    {
        int nr;
        nr=getSumOfNeighborsOnShownMatrix(numberOfLines,numberOfColumns,x,y);
        if(nr==shownMatrix[x][y]-'0')
        {
            char caracter='a';
            if(x>1&&y>1)
                if (shownMatrixBehind2[x-2][y-2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x-2,y-2,caracter);
            if(x>1)
                if (shownMatrixBehind2[x-2][y]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x-2,y,caracter);
            if(x>1&&y<2*numberOfColumns-1)
                if (shownMatrixBehind2[x-2][y+2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x-2,y+2,caracter);
            if(y>1)
                if (shownMatrixBehind2[x][y-2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x,y-2,caracter);
            if(y<2*numberOfColumns-1)
                if (shownMatrixBehind2[x][y+2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x,y+2,caracter);
            if(x<2*numberOfLines-1&&y>1)
                if (shownMatrixBehind2[x+2][y-2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x+2,y-2,caracter);
            if(x<2*numberOfLines-1)
                if (shownMatrixBehind2[x+2][y]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x+2,y,caracter);
            if(x<2*numberOfLines-1&&y<2*numberOfColumns-1)
                if (shownMatrixBehind2[x+2][y+2]==0)
                    uncoverSquare(numberOfLines,numberOfColumns,x+2,y+2,caracter);
        }
        return;
    }

    if(mineMatrix[x/2][y/2]==1)
    {
        //shownMatrix[x][y]=char(254);
        shownMatrix[x][y]='x';
        matchLost=1;
    }
    else
    {
        if(shownMatrix[x][y]!=char(178))
            return;
        numberOfUncoveredSafePlaces--;
        int nr;
        nr=getSumOfNeighbors(numberOfLines,numberOfColumns,x/2,y/2);
        if(nr!=0)
            shownMatrix[x][y]=nr+'0';
        else
        {
            shownMatrix[x][y]=' ';
            char caracter='a';
            if(x>1&&y>1)                                    uncoverSquare(numberOfLines,numberOfColumns,x-2,y-2,caracter);
            if(x>1)                                         uncoverSquare(numberOfLines,numberOfColumns,x-2,y,caracter);
            if(x>1&&y<2*numberOfColumns-1)                  uncoverSquare(numberOfLines,numberOfColumns,x-2,y+2,caracter);
            if(y>1)                                         uncoverSquare(numberOfLines,numberOfColumns,x,y-2,caracter);
            if(y<2*numberOfColumns-1)                       uncoverSquare(numberOfLines,numberOfColumns,x,y+2,caracter);
            if(x<2*numberOfLines-1&&y>1)                    uncoverSquare(numberOfLines,numberOfColumns,x+2,y-2,caracter);
            if(x<2*numberOfLines-1)                         uncoverSquare(numberOfLines,numberOfColumns,x+2,y,caracter);
            if(x<2*numberOfLines-1&&y<2*numberOfColumns-1)  uncoverSquare(numberOfLines,numberOfColumns,x+2,y+2,caracter);
        }
    }
}
void createShownMatrix(int numberOfLines,int numberOfColumns,int numberOfBombs)
{
    int i,j;
    for(i=0;i<=2*numberOfColumns;i=i+2)
    {
        shownMatrix[0][i]=char(194);
        shownMatrix[0][i+1]=char(196);
        shownMatrix[1][i]='|';
    }
    for(i=2;i<=2*numberOfLines;i++)
    {
        shownMatrix[i][0]=char(195);
        for(j=1;j<2*numberOfColumns;j=j+2)
            shownMatrix[i][j]=char(196),shownMatrix[i][j+1]='+';
        shownMatrix[i][j-1]=char(180);
        i++;
        for(j=0;j<=2*numberOfColumns;j=j+2)
            shownMatrix[i][j]='|';
    }
    shownMatrix[0][0]=char(218);
    shownMatrix[2*numberOfLines][0]=char(192);
    shownMatrix[0][2*numberOfColumns]=char(191);
    shownMatrix[2*numberOfLines][2*numberOfColumns]=char(217);
    for(i=2;i<2*numberOfColumns;i=i+2)
        shownMatrix[2*numberOfLines][i]=char(193);
    for(i=1;i<=2*numberOfLines;i=i+2)
        for(j=1;j<=2*numberOfColumns;j=j+2)
            shownMatrix[i][j]=char(178);
}
void createMatrix(int numberOfLines, int numberOfColumns, int numberOfBombs, int lin, int col)
{
    int x,y,i;
    srand(time(NULL));
    for(i=0;i<numberOfBombs;i++)
    {
        x=rand()%numberOfLines;
        y=rand()%numberOfColumns;
        while((lin/2==x&&col/2==y)||mineMatrix[x][y]==1)
        {
            x=rand()%numberOfLines;
            y=rand()%numberOfColumns;
        }
        mineMatrix[x][y]=1;
    }
}
bool isNumber(char s[])
{
    if(strlen (s)>3)
        return 0;
    int n=strlen(s)-1;
    for(;n>0;n--)
    {
        if(!isdigit(s[n]))
            return 0;
    }
    if(s[0]=='-')
        return 1;
    if(!isdigit(s[n]))
        return 0;
    return 1;
}
int getNumber(char s[])
{
    int semn=1,x=0;
    if (s[0]=='-')
    {
        semn=-1;
        strcpy(s,s+1);
    }
    for(unsigned i=0;i<strlen(s);i++)
        x=x*10+(s[i]-'0');
    x=x*semn;
    return x;
}
void correctMistakes(int &numberOfLines,int &numberOfColumns,int &numberOfBombs)
{
    if(numberOfLines<8)
        numberOfLines=8;
    if(numberOfLines>18)
        numberOfLines=18;

    if(numberOfColumns<8)
        numberOfColumns=8;
    if(numberOfColumns>30)
       numberOfColumns=30;

    if(numberOfBombs<8)
        numberOfBombs=8;
    if(numberOfBombs>(numberOfLines-1)*(numberOfColumns-1))
        numberOfBombs=(numberOfLines-1)*(numberOfColumns-1);
}
void flag(int numberOfLines, int numberOfColumns, int x, int y)
{
    if(shownMatrix[x][y]==char(178))
    {
        shownMatrix[x][y]=char(207);
        numberOfRemainingBombs--;
    }
    else
        if(shownMatrix[x][y]==(char(207)))
        {
            shownMatrix[x][y]=char(178);
            numberOfRemainingBombs++;
        }
    SetCursorPosition(numberOfLines*2+1,0);
	cout<<"Mines Count: "<<numberOfRemainingBombs<<"   \n";
}
void removeStars(int numberOfLines, int numberOfColumns, int x, int y)
{
    shownMatrix[x-1][y]=char(196);
    shownMatrix[x][y-1]='|';
    shownMatrix[x][y+1]='|';
    shownMatrix[x+1][y]=char(196);
    if(x==1)
        if(y==1)
        {
            shownMatrix[x-1][y-1]=char(218);
            shownMatrix[x-1][y+1]=char(194);
            shownMatrix[x+1][y-1]=char(195);
            shownMatrix[x+1][y+1]='+';
        }
        else
            if(y==2*numberOfLines-1)
            {
                shownMatrix[x-1][y-1]=char(194);
                shownMatrix[x-1][y+1]=char(191);
                shownMatrix[x+1][y-1]='+';
                shownMatrix[x+1][y+1]=char(180);
            }
            else
            {
                shownMatrix[x-1][y-1]=char(194);
                shownMatrix[x-1][y+1]=char(194);
                shownMatrix[x+1][y-1]='+';
                shownMatrix[x+1][y+1]='+';
            }
    else
        if(x==2*numberOfLines-1)
            if(y==1)
            {
                shownMatrix[x-1][y-1]=char(195);
                shownMatrix[x-1][y+1]='+';
                shownMatrix[x+1][y-1]=char(192);
                shownMatrix[x+1][y+1]=char(193);
            }
            else
                if(y==2*numberOfLines-1)
                {
                    shownMatrix[x-1][y-1]='+';
                    shownMatrix[x-1][y+1]=char(180);
                    shownMatrix[x+1][y-1]=char(193);
                    shownMatrix[x+1][y+1]=char(217);
                }
                else
                {
                    shownMatrix[x-1][y-1]='+';
                    shownMatrix[x-1][y+1]='+';
                    shownMatrix[x+1][y-1]=char(193);
                    shownMatrix[x+1][y+1]=char(193);
                }
        else
            if(y==1)
            {
                shownMatrix[x-1][y-1]=char(195);
                shownMatrix[x-1][y+1]='+';
                shownMatrix[x+1][y-1]=char(195);
                shownMatrix[x+1][y+1]='+';
            }
            else
                if(y==2*numberOfLines-1)
                {
                    shownMatrix[x-1][y-1]='+';
                    shownMatrix[x-1][y+1]=char(180);
                    shownMatrix[x+1][y-1]='+';
                    shownMatrix[x+1][y+1]=char(180);
                }
                else
                {
                    shownMatrix[x-1][y-1]='+';
                    shownMatrix[x-1][y+1]='+';
                    shownMatrix[x+1][y-1]='+';
                    shownMatrix[x+1][y+1]='+';
                }
}
void addStars(int x, int y)
{
    shownMatrix[x-1][y-1]=shownMatrix[x-1][y]=shownMatrix[x-1][y+1]=shownMatrix[x][y-1]='*';
    shownMatrix[x][y+1]=shownMatrix[x+1][y-1]=shownMatrix[x+1][y]=shownMatrix[x+1][y+1]='*';
}
void moveOn(int numberOfLines,int numberOfColumns,int &x, int &y, char key)
{
    if(x==1&&key=='w')
        return;
    if(y==1&&key=='a')
        return;
    if(y==2*numberOfColumns-1&&key=='d')
        return;
    if(x==2*numberOfLines-1&&key=='s')
        return;
    switch(key)
    {
    case 'w':
        removeStars(numberOfLines,numberOfColumns,x,y);
        addStars(x-2,y);
        x=x-2;
        return;
    case 'a':
        removeStars(numberOfLines,numberOfColumns,x,y);
        addStars(x,y-2);
        y=y-2;
        return;
    case 's':
        removeStars(numberOfLines,numberOfColumns,x,y);
        addStars(x+2,y);
        x=x+2;
        return;
    case 'd':
        removeStars(numberOfLines,numberOfColumns,x,y);
        addStars(x,y+2);
        y=y+2;
        return;
    }
}
void safeDiscover(int numberOfLines, int numberOfColumns, int x, int y)
{
    if(x>1)
    {
        if(shownMatrix[x-2][y]==char(178))
            shownMatrix[x-2][y]=char(176);
        if(y>1)
            if(shownMatrix[x-2][y-2]==char(178))
                shownMatrix[x-2][y-2]=char(176);
        if(y<2*numberOfColumns-1)
            if(shownMatrix[x-2][y+2]==char(178))
                shownMatrix[x-2][y+2]=char(176);
    }
    if(x<2*numberOfLines-1)
    {
        if(shownMatrix[x+2][y]==char(178))
            shownMatrix[x+2][y]=char(176);
        if(y>1)
            if(shownMatrix[x+2][y-2]==char(178))
                shownMatrix[x+2][y-2]=char(176);
        if(y<2*numberOfColumns-1)
            if(shownMatrix[x+2][y+2]==char(178))
                shownMatrix[x+2][y+2]=char(176);
    }
    if(y>1)
        if(shownMatrix[x][y-2]==char(178))
            shownMatrix[x][y-2]=char(176);
    if(y<2*numberOfColumns-1)
        if(shownMatrix[x][y+2]==char(178))
            shownMatrix[x][y+2]=char(176);
}
void safeUndiscover(int numberOfLines, int numberOfColumns, int x, int y)
{
    if(x>1)
    {
        if(shownMatrix[x-2][y]==char(176))
            shownMatrix[x-2][y]=char(178);
        if(y>1)
            if(shownMatrix[x-2][y-2]==char(176))
                shownMatrix[x-2][y-2]=char(178);
        if(y<2*numberOfColumns-1)
            if(shownMatrix[x-2][y+2]==char(176))
                shownMatrix[x-2][y+2]=char(178);
    }
    if(x<2*numberOfLines-1)
    {
        if(shownMatrix[x+2][y]==char(176))
            shownMatrix[x+2][y]=char(178);
        if(y>1)
            if(shownMatrix[x+2][y-2]==char(176))
                shownMatrix[x+2][y-2]=char(178);
        if(y<2*numberOfColumns-1)
            if(shownMatrix[x+2][y+2]==char(176))
                shownMatrix[x+2][y+2]=char(178);
    }
    if(y>1)
        if(shownMatrix[x][y-2]==char(176))
            shownMatrix[x][y-2]=char(178);
    if(y<2*numberOfColumns-1)
        if(shownMatrix[x][y+2]==char(176))
            shownMatrix[x][y+2]=char(178);
}
void pressKey(int numberOfLines,int numberOfColumns,int &x, int &y)
{
    kbhit();
    char key;
    key=getch();
    if(ok==0)
    {
        char wasd[]="wasd";
        if (strchr(wasd,key))
            moveOn(numberOfLines,numberOfColumns,x,y,key);
        else
            if(key==' ')
            {
                char caracter=' ';
                uncoverSquare(numberOfLines,numberOfColumns,x,y,caracter);
            }
            else
                if(key=='f')
                    flag(numberOfLines,numberOfColumns,x,y);
                else
                    if(key=='z')
                    {
                        ok=1;
                        safeDiscover(numberOfLines,numberOfColumns,x,y);
                    }
                    else
                        pressKey(numberOfLines,numberOfColumns,x,y);
    }
    else
    {
        if(key=='z')
        {
            safeUndiscover(numberOfLines,numberOfColumns,x,y);
            ok=0;
        }
        else
            pressKey(numberOfLines,numberOfColumns,x,y);
    }
}
char firstPressKey(int numberOfLines,int numberOfColumns,int &x, int &y)
{
    kbhit();
    char key;
    key=getch();
    char wasd[]="wasd";
    if (strchr(wasd,key))
        moveOn(numberOfLines,numberOfColumns,x,y,key);
    else
        if(key==' ')
            return ' ';
        else
            if(key=='f')
                flag(numberOfLines,numberOfColumns,x,y);
            else
                return firstPressKey(numberOfLines,numberOfColumns,x,y);
    return key;
}
void initialPoint(int &x, int &y)
{
    x=1;
    y=1;
    shownMatrix[0][0]=shownMatrix[0][1]=shownMatrix[0][2]=shownMatrix[1][0]='*';
    shownMatrix[1][2]=shownMatrix[2][0]=shownMatrix[2][1]=shownMatrix[2][2]='*';
}
void clearscreen()
{
	SetCursorPosition(0,0);
}
void printCharInColor(int x, int y)
{
    switch (shownMatrix[x][y])
    {
    case '1':
        setColor(9); //bright blue
        cout<<shownMatrix[x][y]<<' ';
        setColor(8); // gray-reset
        break;
    case '2':
        setColor(10); //bright green
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '3':
        setColor(12); //bright red
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '4':
        setColor(1); //blue
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '5':
        setColor(4); //red
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '6':
        setColor(3); //teal
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '7':
        setColor(7); //white-gray
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case '8':
        setColor(8); // gray
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case char(178): //uncovered
        setColor(8); // gray
        cout<<shownMatrix[x][y]<<' ';
        break;
    case char(207): // Flag
        setColor(0); //black
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case char(254): // game over
        setColor(14); //bright yellow
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case 'x':    //game over on [x][y]
        setColor(0); //black
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    case 'w':   //wrong flag
        setColor(5); //purple
        cout<<shownMatrix[x][y]<<' ';
        setColor(8);
        break;
    default:
        setColor(8); //gray
        cout<<shownMatrix[x][y]<<' ';
        break;
    }
}
void printShownMatrix(int numberOfLines, int numberOfColumns)
{
    clearscreen();
    for(int i=0;i<=2*numberOfLines;i++)
    {
        for(int j=0;j<=2*numberOfColumns;j++)
            printCharInColor(i,j);
        cout<<'\n';
    }
    cout<<"Mines Count: "<<numberOfRemainingBombs<<"   \n";
}
void printStarsInColors2(int x, int y)
{
    SetCursorPosition(x-1,y*2-2);
    setColor(12);   cout<<"* ";
    setColor(6);    cout<<"* ";
    setColor(14);   cout<<"* ";
    SetCursorPosition(x,y*2-2);
    setColor(5);   cout<<"* ";
    if(shownMatrix[x][y]==char(178))
    {
        setColor(0);
        cout<<char(178)<<' ';
    }
    else
        printCharInColor(x,y);
    setColor(10);   cout<<"* ";
    SetCursorPosition(x+1,y*2-2);
    setColor(13);    cout<<"* ";
    setColor(9);   cout<<"* ";
    setColor(11);    cout<<"* ";
    setColor(8);

}
void printStarsInColors(int x, int y)
{
    SetCursorPosition(x-1,y*2-2);
    setColor(0);
    cout<<"* ";
    cout<<"* ";
    cout<<"* ";
    SetCursorPosition(x,y*2-2);
    cout<<"* ";
    if(shownMatrix[x][y]==char(178))
    {
        setColor(0);
        cout<<char(178)<<' ';
    }
    else
        printCharInColor(x,y);
    setColor(0);
    cout<<"* ";
    SetCursorPosition(x+1,y*2-2);
    cout<<"* ";
    cout<<"* ";
    cout<<"* ";
    setColor(8);

}
void changeNearbySquares (int x, int y)
{
    SetCursorPosition(x-1,y*2-2);
	cout<<shownMatrix[x-1][y-1]<<' '<<shownMatrix[x-1][y]<<' '<<shownMatrix[x-1][y+1];
	SetCursorPosition(x,y*2-2);
	cout<<shownMatrix[x][y-1]<<' ';
	printCharInColor(x,y);
	cout<<shownMatrix[x][y+1];
	SetCursorPosition(x+1,y*2-2);
	cout<<shownMatrix[x+1][y-1]<<' '<<shownMatrix[x+1][y]<<' '<<shownMatrix[x+1][y+1];
}
void changeNeighborSquares(int numberOfLines, int numberOfColumns, int x, int y)
{
    changeNearbySquares(x,y);
    if(x>1&&y>1)
    {
        changeNearbySquares(x-2,y-2);
        if (shownMatrix[x-2][y-2]==' '&&shownMatrixBehind[x-2][y-2]==0)
        {
            shownMatrixBehind[x-2][y-2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x-2,y-2);
        }
    }
    if(x>1)
    {
        changeNearbySquares(x-2,y);
        if (shownMatrix[x-2][y]==' '  &&shownMatrixBehind[x-2][y]==0)
        {
            shownMatrixBehind[x-2][y]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x-2,y);
        }
    }
    if(x>1&&y<2*numberOfColumns-1)
    {
        changeNearbySquares(x-2,y+2);
        if (shownMatrix[x-2][y+2]==' '&&shownMatrixBehind[x-2][y+2]==0)
        {
            shownMatrixBehind[x-2][y+2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x-2,y+2);
        }
    }
    if(y>1)
    {
        changeNearbySquares(x,y-2);
        if (shownMatrix[x][y-2]==' '  &&shownMatrixBehind[x][y-2]==0)
        {
            shownMatrixBehind[x][y-2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x,y-2);
        }
    }
    if(y<2*numberOfColumns-1)
    {
        changeNearbySquares(x,y+2);
        if (shownMatrix[x][y+2]==' '  &&shownMatrixBehind[x][y+2]==0)
        {
            shownMatrixBehind[x][y+2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x,y+2);
        }
    }
    if(x<2*numberOfLines-1&&y>1)
    {
        changeNearbySquares(x+2,y-2);
        if (shownMatrix[x+2][y-2]==' '&&shownMatrixBehind[x+2][y-2]==0)
        {
            shownMatrixBehind[x+2][y-2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x+2,y-2);
        }
    }
    if(x<2*numberOfLines-1)
    {
        changeNearbySquares(x+2,y);
        if (shownMatrix[x+2][y]==' '  &&shownMatrixBehind[x+2][y]==0)
        {
            shownMatrixBehind[x+2][y]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x+2,y);
        }
    }
    if(x<2*numberOfLines-1&&y<2*numberOfColumns-1)
    {
        changeNearbySquares(x+2,y+2);
        if (shownMatrix[x+2][y+2]==' '&&shownMatrixBehind[x+2][y+2]==0)
        {
            shownMatrixBehind[x+2][y+2]=1;
            changeNeighborSquares(numberOfLines,numberOfColumns,x+2,y+2);
        }
    }
    SetCursorPosition(2*numberOfLines+1,0);
    //delete the following lines for only gray cursor
    //if(shownMatrix[x-1][y-1]=='*'&&shownMatrix[x-1][y+1]=='*'&&shownMatrix[x+1][y-1]=='*'&&shownMatrix[x+1][y+1]=='*')
    //{
     //   printStarsInColors(x,y);
     //   return;
    //}
}
void resetFreeVariables()
{
    numberOfUncoveredSafePlaces=0;
    ok=0;
    rules=0;
    matchLost=0;
    playAgain=0;
    for(int i=0;i<100;i++)
        for(int j=0;j<100;j++)
            mineMatrix[i][j]=shownMatrix[i][j]=shownMatrixBehind[i][j]=shownMatrixBehind2[i][j]=0;
}
char pressSmallKey()
{
    char key;
    kbhit();
    key=getch();
    return key;
}
void printLose(int numberOfLines, int numberOfColumns,int x, int y)
{
    clearscreen();
    for(int i=0;i<=2*numberOfLines;i++)
    {
        for(int j=0;j<=2*numberOfColumns;j++)
        {
            if(i==x&&j==y);
                //shownMatrix[i][j]='x';
            else if(i%2==1&&j%2==1&&mineMatrix[i/2][j/2]==1)
                if(shownMatrix[i][j]!=char(207)&&shownMatrix[i][j]!='x')
                    shownMatrix[i][j]=char(254);
                else;
            else if(i%2==1&&j%2==1&&mineMatrix[i/2][j/2]==0&&shownMatrix[i][j]==char(207))
                shownMatrix[i][j]='w';
            printCharInColor(i,j);
        }
        cout<<'\n';
    }
    cout<<"Mines Count: "<<numberOfRemainingBombs<<"   \n";
}
void printWin(int numberOfLines, int numberOfColumns)
{
    clearscreen();
    for(int i=0;i<=2*numberOfLines;i++)
    {
        for(int j=0;j<=2*numberOfColumns;j++)
        {
            if (shownMatrix[i][j]==char(178))
                shownMatrix[i][j]=char(207);
            printCharInColor(i,j);
        }
        cout<<'\n';
    }
    cout<<"Mines Count: "<<numberOfRemainingBombs<<"   \n";
}
void printRules()
{
    cout<<"Do you need help with the game's rules?(Y/N)\n";
    while(1!=0)
    {
        char key=pressSmallKey();
        if(key=='y')
        {
            rules=1;
            cout<<"\nThe rules in Minesweeper are simple:\n\n";
            cout<<"*Uncover a mine, and the game ends.\n";
            cout<<"*Uncover an empty square, and you keep playing.\n";
            cout<<"*Uncover a number, and it tells you how many mines \nlay hidden in the eight surrounding ";
            cout<<"squares:\ninformation you use to deduce which nearby squares are safe to click.\n\n";
            cout<<"Use WASD to move your cursor around, SPACE to uncover a square,\n";
            cout<<"F to put a flag on a square, Z for safe-discovering a bigger area \n";
            cout<<"around your cursor.\n";
            break;
    }
    else
        if(key=='n')
            break;
    }
}
void chooseDifficulty(int &numberOfLines, int &numberOfColumns, int &numberOfBombs, char difficulty[])
{
    char s[10],key;
    cout<<"\nChoose your difficulty:\n";
    cout<<" **Easy** |   Medium   |   Expert   |   Custom   \n";
    strcpy(s,"Easy");
    while(1!=0)
    {
        key=pressSmallKey();
        if(key=='d')
        {
            if(strcmp(s,"Easy")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<"   Easy   | **Medium** |   Expert   |   Custom   \n";
                strcpy(s,"Medium");
            }
            else if(strcmp(s,"Medium")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<"   Easy   |   Medium   | **Expert** |   Custom   \n";
                strcpy(s,"Expert");
            }
            else if (strcmp(s,"Expert")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<"   Easy   |   Medium   |   Expert   | **Custom** \n";
                strcpy(s,"Custom");
            }
        }
        if(key=='a')
        {
            if(strcmp(s,"Medium")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<" **Easy** |   Medium   |   Expert   |   Custom   \n";
                strcpy(s,"Easy");
            }
            else if(strcmp(s,"Expert")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<"   Easy   | **Medium** |   Expert   |   Custom   \n";
                strcpy(s,"Medium");
            }
            else if (strcmp(s,"Custom")==0)
            {
                if(rules==1)
                    SetCursorPosition(19,0);
                else
                    SetCursorPosition(7,0);
                cout<<"   Easy   |   Medium   | **Expert** |   Custom   \n";
                strcpy(s,"Expert");
            }
        }
        if(key==' ')
            break;
    }
    int n;
    if(s[1]=='a') n=1;
    if(s[1]=='e') n=2;
    if(s[1]=='x') n=3;
    if(s[1]=='u') n=4;
    strcpy(difficulty,s);
    switch(n)
    {
    case 1:
        numberOfLines=8;
        numberOfColumns=8;
        numberOfBombs=10;
        break;
    case 2:
        numberOfLines=14;
        numberOfColumns=14;
        numberOfBombs=35;
        break;
    case 3:
        numberOfLines=18;
        numberOfColumns=18;
        numberOfBombs=70;
        break;
    case 4:
        cout<<"Height: ";
        gets(s);
        while(!isNumber(s))
        {
            cout<<"Invalid Number! Please input a vald number!\nHeight: ";
            gets(s);
        }
        numberOfLines=getNumber(s);
        cout<<"Width: ";
        gets(s);
        while(!isNumber(s))
        {
            cout<<"Invalid Number! Please input a vald number!\nWidth: ";
            gets(s);
        }
        numberOfColumns=getNumber(s);
        cout<<"Number of mines: ";
        gets(s);
        while(!isNumber(s))
        {
            cout<<"Invalid Number! Please input a vald number!\nNumber of mines: ";
            gets(s);
        }
        numberOfBombs=getNumber(s);
        break;
    }
    correctMistakes(numberOfLines,numberOfColumns,numberOfBombs);
    numberOfRemainingBombs=numberOfBombs;
    numberOfUncoveredSafePlaces=numberOfLines*numberOfColumns-numberOfBombs;
}
void scorRecord2(int x,char difficulty[]) //not used
{
    char s1[100],s2[100],s3[100];
    fstream f;
    f.open("score", fstream::in);
    f.get(s1,64);
    f.get(s2,64);
    f.get(s3,64);
    f.close();
    int n;
    switch(difficulty[1])
    {
    case 'a':
        decrypt(n,s1);
        if(x<n)
            encrypt(x,s1);
        break;
    case 'e':
        decrypt(n,s2);
        if(x<n)
            encrypt(x,s2);
        break;
    case 'x':
        decrypt(n,s3);
        if(x<n)
            encrypt(x,s3);
        break;
    case 'u':
        break;
    }
    cout<<"\nYour score: "<<x<<'s';
    if(difficulty[1]!='u')
        cout<<"\nHighest score: "<<n<<'s';
    if(x<=n)
        cout<<"\n\nCongratulations! New high score!";
    f.open("score", fstream::out);
    f<<s1<<s2<<s3;
    f.close();
}
void scorRecord(int x, char difficulty[])
{
    cout<<"\nYour score: "<<x<<'s'<<'\n';
    char s[15];
    fstream f;
    int scoreEasy,scoreMedium,scoreExpert,isOk=1,n;
    f.open("score",fstream::in);
    f.getline(s,15);
    if(0>=strlen(s))
    {
        scoreEasy=scoreMedium=scoreExpert=999;
        isOk=0;
    }
    for(int i=0;i<strlen(s);i++)
        if(!isdigit(s[i])&&s[i]!=' ')
        {
            scoreEasy=scoreMedium=scoreExpert=999;
            isOk=0;
        }
    f.close();
    f.open("score",fstream::in);
    if(isOk)
        f>>scoreEasy>>scoreMedium>>scoreExpert;
    switch(difficulty[1])
    {
    case 'a':
        n=scoreEasy;
        break;
    case 'e':
        n=scoreMedium;
        break;
    case 'x':
        n=scoreExpert;
        break;
    default:
        break;
    }
    f.close();
    if(difficulty[1]!='u')
        cout<<"Highest score for \""<<difficulty<<"\" difficulty is: "<<n<<'s'<<'\n';
    if(x<n)
    {
        if(difficulty[1]!='u')
            cout<<"\nCongratulations! New high-score!\n";
        switch(difficulty[1])
        {
        case 'a':
            scoreEasy=x;
            break;
        case 'e':
            scoreMedium=x;
            break;
        case 'x':
            scoreExpert=x;
            break;
        default:
            break;
        }
    }
    SetFileAttributes("score", FILE_ATTRIBUTE_NORMAL);
    f.open("score",fstream::out);
    f<<scoreEasy<<' '<<scoreMedium<<' '<<scoreExpert;
    f.close();
    SetFileAttributes("score", FILE_ATTRIBUTE_HIDDEN);
}
void play(int numberOfLines, int numberOfColumns, int numberOfBombs, char difficulty[])
{
    printShownMatrix(numberOfLines,numberOfColumns);
    int x,y;
    char c;
    initialPoint(x,y);
    changeNeighborSquares(numberOfLines,numberOfColumns,x,y);
    while(1!=0)
    {
        c=firstPressKey(numberOfLines,numberOfColumns,x,y);
        changeNeighborSquares(numberOfLines,numberOfColumns,x,y);
        if(c==' '||c==char(207))
        {
            createMatrix(numberOfLines,numberOfColumns,numberOfBombs,x,y);
            uncoverSquare(numberOfLines,numberOfColumns,x,y,c);
            changeNeighborSquares(numberOfLines,numberOfColumns,x,y);
            if(numberOfUncoveredSafePlaces==0)
            {
                printWin(numberOfLines,numberOfColumns);
                SetCursorPosition(numberOfLines*2+2,0);
                cout<<"\nYou've Won!";
                scorRecord(0,difficulty);
                cout<<"\n\nNew game?(Y/N)\n";
                while(1!=0)
                {
                    char key=pressSmallKey();
                    if(key=='n')
                    {
                        playAgain=0;
                        goto ending;
                    }
                    else
                        if(key=='y')
                        {
                            playAgain=1;
                            goto ending;
                        }
                }
            }
            break;
        }
    }
    clock_t start;
    start=clock();
    double timp;
    while(1)
    {
        pressKey(numberOfLines,numberOfColumns,x,y);
        if(matchLost==1)
        {
            changeNeighborSquares(numberOfLines,numberOfColumns,x,y);
            printLose(numberOfLines,numberOfColumns,x,y);
            SetCursorPosition(numberOfLines*2+2,0);
            cout<<"\nGAME OVER";
            break;
        }
        changeNeighborSquares(numberOfLines,numberOfColumns,x,y);
        cout<<'\n';
        if(numberOfUncoveredSafePlaces==0)
        {
            printWin(numberOfLines,numberOfColumns);
            SetCursorPosition(numberOfLines*2+2,0);
            cout<<"\nYou've Won!";
            timp=(clock()-start)/(double) CLOCKS_PER_SEC;
            timp=floor(timp);
            if(timp>999)
                timp=999;
            scorRecord((int)timp,difficulty);
            break;
        }
    }
    cout<<"\n\nNew game?(Y/N)\n";
    while(1!=0)
{
    char key=pressSmallKey();
    if(key=='n')
    {
        playAgain=0;
        break;
    }
    else
        if(key=='y')
        {
            playAgain=1;
            break;
        }
}
ending:;
}
