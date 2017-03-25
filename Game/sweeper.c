#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <ctype.h>
#include <dirent.h>
#include <string.h>
#include <windows.h>
#include<pthread.h>
#define MAX 32
int remainOfFlags;
int movesDone = 0;
int opened = 0;
int timeEnd = 0;
int flagsPlaced=0,questionsPlaced=0;
int initialAssign = 0;
double diff_t;
int threadnum1 =1,threadnum2 =1,threadnum3 =1;
int* exitCount,*h,*w, *heightForLoad, *widthForLoad;
clock_t* start1_t;
clock_t now_t;
typedef struct
{
    int mine;
    int open ;
    int banned;
    int question;
    int flag;
    int minesArround;
    int mineExplode;
} cell;
char charScanner(int modeOfScan) /*scans characters*/
{
    char character;
    if(modeOfScan == 1) /*scans characters from the user with their validation*/
    {
        while(scanf(" %c",&character) != 1||getchar() != '\n')
        {
            printf("\t\t\t\t\tPlease enter a valid choice : ");
            while(getchar() != '\n');
        }
        fflush(stdin);
        return character;
    }
    else if(modeOfScan == 2) /*scans an enter from the user*/
    {
        do
        {
            scanf ("%c",&character);
        }
        while(character!='\n');
        return character;
    }
}
int intScanner(char modeOfScan) /*scans an integer form the user*/
{
    int integer;
    if(modeOfScan == 'u') /*scans the integer with its validation*/
    {
        int tmp;
        do
        {
            tmp = 0;
            while((tmp =scanf(" %d",&integer)) != 1||getchar() != '\n')
            {
                printf("\t\t\t\t\tPlease enter a valid choice : ");
                while(getchar() != '\n');
            }
            if(tmp && (integer<1||integer>5))
            {
                printf("\t\t\t\t\tPlease enter a valid choice : ");
            }

        }while (integer<1||integer>5);
        fflush(stdin);
        return integer;
    }
}
void *timerCheckMove(cell arr[MAX][MAX])/*takes the array as an argument*/
{
    time_t t = time(NULL);/*a variable that holds the starting time of the function after the thread is called*/
    do
    {
        while((difftime(time(NULL),t))<60&&threadnum1)/*thread num is considered to be the key of the thread it has a n
            initial value of 1 but when the user enters an input it acquires the value of 0 so it leaves the loop
            when  60 sec passes and the user is idle it enters the following step*/
        {}
        if (threadnum1)
            /*checks if the user entered something or not*/
        {
            clear();/*clearing the screen*/
            draw(arr, *h,*w);/*drawing the grid*/
            now_t = clock() / CLOCKS_PER_SEC;/*gets the time in this moment*/
            UI(*start1_t, now_t);
            printf("\t\t\t\t\tO :open , Q : question , F : flag\n\t\t\t\t\tU : unmark , E : exit , S : save\n");
            printf("\t\t\t\t\tEnter the type of your move:");
            t = time(NULL);/*renewing the time variable*/
        }
    }
    while (threadnum1);
}
void *timerRow(cell arr[MAX][MAX])/*same as previous*/
{
    time_t t = time(NULL);
    do
    {
        while((difftime(time(NULL),t))<60&&threadnum3)
        {}
        if (threadnum3)
        {
            clear();
            draw(arr, *h,*w);
            now_t = clock() / CLOCKS_PER_SEC;
            UI(*start1_t-1, now_t);
            printf("\t\t\t\t\tPlease enter the row number:");
            t = time(NULL);
        }
    }
    while (threadnum3);
}
void *timerColumn(cell arr[MAX][MAX])
{
    time_t t = time(NULL);
    do
    {
        while((difftime(time(NULL),t))<60&&threadnum2)
        {}
        if (threadnum2)
        {
            clear();
            draw(arr, *h,*w);
            now_t = clock() / CLOCKS_PER_SEC;
            UI(*start1_t, now_t);
            printf("\t\t\t\t\tPlease enter the column number:");
            t = time(NULL);
        }
    }
    while (threadnum2);
}
void colorExplode(void)
{
    /*the function creates a handle through it we can change the color of the text and its back ground*/
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);/*the current running console application*/
    SetConsoleTextAttribute(hConsole,  BACKGROUND_RED|BACKGROUND_INTENSITY);
}
void colorRed(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED |FOREGROUND_INTENSITY| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED|BACKGROUND_INTENSITY);
}
void colorBlue(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED|BACKGROUND_INTENSITY);
}
void colorBlack(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED|BACKGROUND_INTENSITY);
}
void colorPurple(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED|BACKGROUND_INTENSITY);
}
void colorGreen(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN|FOREGROUND_BLUE|FOREGROUND_RED| FOREGROUND_INTENSITY | BACKGROUND_GREEN |BACKGROUND_INTENSITY);
}
void colorGray(void)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED |FOREGROUND_INTENSITY| BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
}
void clear(void)
{
    system("cls"); /*clears the screen*/
}
void welcome (void)
{
    system("COLOR FC");
    char c[]="\n\n\t\t\t\t\tWelcome to minesweeper game :D\n\t\t\t\t\t  We wish you lots of fun ;)\n\n";
    int i;
    for(i = 0 ; i<strlen(c); i++) /*printing the welcome message one leter at a time with an interval of 60 ms between each*/
    {
        printf("%c",c[i]);
        Sleep(60);
    }
    system("COLOR A3");/*changing the color of the text and background several times with time intervals .4 sec*/
    Sleep(400);
    system("COLOR D5");
    Sleep(400);
    system("COLOR E1");
    Sleep(400);
    system("COLOR C8");
    Sleep(400);
    system("COLOR B9");
    Sleep(400);
    system("COLOR F1");
    Sleep(400);
}
void menu(void) /*main menu of the game*/
{
    printf("\n\t\t\t\t\tMain menu :\n\n\
\t\t\t\t\tChoose 1 , 2 , 3 , 4 or 5 :\n\n\
\t\t\t\t\t1 - Start a new game.\n\n\
\t\t\t\t\t2 - Load game.\n\n\
\t\t\t\t\t3 - View high scores.\n\n\
\t\t\t\t\t4 - User Manual.\n\n\
\t\t\t\t\t5 - Exit.\n\n");
}
int initialize (cell arr[MAX][MAX],int height,int width) /*initialize the grid*/
{
    int i, j;/*counters*/
    for(i = 0 ; i<height+2; i++)
    {
        for (j =0 ; j<width+2; j++)
        {
            /*assign all the attributes with its initial values of zero and assign the padding*/
            arr[i][j].flag=0;
            arr[i][j].mine=0;
            arr[i][j].open=0;
            arr[i][j].question=0;
            arr[i][j].minesArround=0;
            arr[i][j].mineExplode=0;
            if ((i == 0 || i == height +1)||(j==0||j== width +1))
            {
                arr[i][j].banned=1;/*means that we can't change it during the game*/
            }
            else
            {
                arr[i][j].banned=0;
            }
        }
    }
}
void firstMove(cell arr[MAX][MAX],int height,int width) /*users first move*/
{
    int exitVar = 0;
    int saves=0;
    int minesNumber = 1 + (height*width)/10; /*calculating mines number*/
    if(initialAssign == 0) /*assigned as zero at the beginning of first move only*/
    {
        movesDone=0;
        questionsPlaced=0;
        flagsPlaced=0;
        remainOfFlags = minesNumber;
    }
    else
    {
        initialAssign=0;
    }
    int k=0, i,j, u, q;
    int xCoordinate, yCoordinate ;
    char moveType; /*scanning the user's choice*/
    do
    {
        clear();
        draw(arr,height,width);
        UI(0,0);
        printf("\t\t\t\t\tO :open , Q : question , F : flag\n\t\t\t\t\tE : exit , U: unmark\n");
        printf("\t\t\t\t\tEnter the type of your move:");
        moveType = charScanner(1);
        int tmp =(moveType=='O'||moveType=='E'||moveType=='F'||moveType=='Q'||moveType=='U'||moveType=='o'||moveType=='e'||moveType=='f'||moveType=='q'||moveType=='u');
        if (!tmp)
        {
            printf("\t\t\t\t\tThis move is not valid\n\t\t\t\t\tTry again\n");
            Sleep(1500);
        }

    }
    while(!(moveType=='O'||moveType=='E'||moveType=='F'||moveType=='Q'||moveType=='U'||moveType=='o'||moveType=='e'||moveType=='f'||moveType=='q'||moveType=='u'));
    if (moveType=='E' || moveType=='e')/*user's request to exit*/
    {
        printf("\t\t\t\t\tDo you really want to exit?\n\t\t\t\t\tY : yes\tN : no\n\t\t\t\t\tYour choice :");
        char choice;
        choice = charScanner(1);
        if(choice == 'Y' || choice == 'y')/*yes to exit*/
        {
            timeEnd=0;
            *exitCount=1;
        }
        else if(choice == 'N'||choice == 'n')/*no to continue the game*/
        {
            exitVar = 1;
            initialAssign=1;
            clear();
            draw(arr,height,width);
            UI(0,0);
            firstMove(arr,height,width);
        }
        else
        {
            exitVar = 1;
            printf("\t\t\t\t\tThis move is not valid\n\t\t\t\t\tTry again\n");
            initialAssign=1;
            Sleep(1500);
            clear();
            draw(arr,height,width);
            UI(0,0);
            firstMove(arr,height,width);
        }
    }
    if (!*exitCount&&!exitVar)/*if the user did not save or requested to exit or said no on exit request*/
    {
        clear();
        draw(arr,height,width);
        UI(0,0);
        printf("\t\t\t\t\tPlease enter the row number:"); /*scans the row number from the user*/
        while((scanf(" %d",&xCoordinate) != 1)||(xCoordinate > height || xCoordinate < 1)||getchar() != '\n')
        {
            printf("\t\t\t\t\tthis is not a valid choice\n\t\t\t\t\ttry again ",height);
            Sleep(1500);
            clear();
            draw(arr,height,width);
            UI(0,0);
            printf("\t\t\t\t\tThe row must be between 1 and %d \n\t\t\t\t\tPlease enter the row number: ",height);
            while(getchar() != '\n'); /*checks validity*/
        }
        clear();
        draw(arr,height,width);
        UI(0,0);
        printf("\t\t\t\t\tPlease enter the column number:"); /*scans column number form the user*/
        while((scanf(" %d",&yCoordinate) != 1)||(yCoordinate > width || yCoordinate < 1)||getchar() != '\n')
        {
            printf("\t\t\t\t\tthis is not a valid choice\n\t\t\t\t\ttry again ",width);
            Sleep(1500);
            clear();
            draw(arr,height,width);
            UI(0,0);
            printf("\t\t\t\t\tThe column must be between 1 and %d \n\t\t\t\t\tPlease enter the column number: ",width);
            while(getchar() != '\n');/*checks validity*/
        }
        fflush(stdin);

        if (moveType=='O'||moveType == 'o') /*users's request to open a cell*/
        {
            if (arr[xCoordinate][yCoordinate].flag==1) /*can not open if cell has a flag*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else if (arr[xCoordinate][yCoordinate].question==1)/*can not open if cell ha a question*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else
            {
                /*random mine initializing using the preset range of srand*/
                while(k<minesNumber)
                {
                    i = rand()%(height+2); /*random x-coordinate*/
                    j = rand()%(width+2); /*random y-coordinate*/
                    if(i == xCoordinate && j == yCoordinate) /*cannot put a mine in the entry coordinates of the user*/
                    {
                        continue;
                    }
                    else if(i==0 || j==0 || i==height+1 || j==width+1) /*cannot put a mine in the padding*/
                    {
                        continue;
                    }
                    else if(arr[i][j].mine == 1)/*you cannot place a mine over a mine*/
                    {
                        i = rand()%height;
                        j = rand()%width;
                        continue;
                    }
                    else
                    {
                        arr[i][j].mine = 1;/*it is now safe to place this mine*/
                    }
                    k++; /*increment the number of remaining mines*/
                }
                /*counting the mines around each cell*/
                for(i = 1 ; i<height+1; i++)/*across the column*/
                {
                    for (j = 1 ; j<width+1; j++)/*across the row*/
                    {
                        for(q=-1; q<2; q++)/*up and down directions*/
                        {
                            for(u=-1; u<2; u++)/*left and right directions*/
                            {
                                /*combinations of u variable and q variable leads to counting mines in all 8 directions around the cell*/
                                if(arr[i+q][j+u].mine==1&&(q!=0||u!=0))/*not counting the cell*/
                                {
                                    arr[i][j].minesArround++; /*counting the around mines*/
                                }
                            }
                        }
                    }
                }
                movesDone++; /*incrementing the moves*/
                openCell(arr,height,width,xCoordinate,yCoordinate); /*opening the requested cell*/
            }
        }
        else if (moveType=='Q' || moveType == 'q') /*user's request to place a question*/
        {
            if (arr[xCoordinate][yCoordinate].flag==1) /*cannot place a question over a flag*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else if (arr[xCoordinate][yCoordinate].question==1)/*cannot place a question over a question*/
            {
                printf("\t\t\t\t\tThis one already has a question mark !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else
            {
                movesDone++; /*incrementing moves*/
                questionsPlaced++;/*incrementing questions placed*/
                arr[xCoordinate][yCoordinate].question=1; /*placing a question*/
                clear();
                logger(arr,height,width);/*for debug*/
                draw(arr,height,width);/*redraw the grid*/
                UI(0,0);
                initialAssign=1;
                firstMove(arr,height,width);
            }

        }
        else if (moveType=='F'||moveType=='f')/*user's request to place a flag*/
        {
            if(remainOfFlags == 0)/*user is set only to a limit amount of flags = mines number*/
            {
                printf("\t\t\t\t\tYou can not place any more flags!\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else if (arr[xCoordinate][yCoordinate].flag==1)/*cannot place a flag over a flag*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else if (arr[xCoordinate][yCoordinate].question==1)/*cannot place a flag over a question*/
            {
                printf("\t\t\t\t\tThis one already has a question mark !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else
            {
                movesDone++;/*incrementing moves*/
                remainOfFlags--;/*decrementing the remaining flags*/
                flagsPlaced++;/*incrementing the flags placed*/
                initialAssign=1;
                arr[xCoordinate][yCoordinate].flag = 1; /*placing a flag*/
                clear();
                draw(arr,height,width);/*redraw the grid*/
                logger(arr,height,width);/*for debug*/
                firstMove(arr,height,width);

            }
        }
        else if (moveType=='U'||moveType=='u')/*user's request to remove a flag or a question mark*/
        {

            if (arr[xCoordinate][yCoordinate].flag==0&&arr[xCoordinate][yCoordinate].question==0)/*cannot unmark what is not marked*/
            {
                printf("\t\t\t\t\tThis one is not marked !\n\t\t\t\t\ttry again\n");
                initialAssign=1;
                Sleep(1500);
                clear();
                draw(arr,height,width);
                UI(0,0);
                firstMove(arr,height,width);
            }
            else
            {
                movesDone++;/*incrementing the moves*/
                initialAssign=1;
                /*if the unmark is assigned to flag, the question does not exist*/
                /*and vice versa*/
                if(arr[xCoordinate][yCoordinate].question == 0)/*unmarking a flag*/
                {
                    remainOfFlags ++;/*incrementing the remaining flags*/
                    flagsPlaced--; /*decrementing the placed flags*/
                    arr[xCoordinate][yCoordinate].flag=0; /*removing the flag*/
                    clear();
                    draw(arr,height,width);/*redraw the grid*/
                    UI(0,0);
                    firstMove(arr,height,width);
                }
                else /*unmarking a question*/
                {
                    questionsPlaced--; /*decrementing the questions placed*/
                    arr[xCoordinate][yCoordinate].question=0; /*removing the question*/
                    clear();
                    draw(arr,height,width); /*redrawing the grid*/
                    UI(0,0);
                    firstMove(arr,height,width);
                }
                logger(arr,height,width);
            }
        }
    }
}
void draw (cell arr[MAX][MAX],int height,int width) /*grid drawer*/
{
    int i, j;
    printf("\n\n\n\t\t\t\t\t    ");
    for (j = 1 ; j<width+1; j++) /*drawing the column numbers*/
    {
        if (j<10)
        {
            printf("  %d ",j);
        }
        else
        {
            printf(" %d ",j);
        }
    }
    printf("\n\t\t\t\t\t    +"); /*part of the grid shape*/
    for (j = 1 ; j<width+1; j++)
    {
        printf("---+");
    }
    printf("\n");
    for(i = 1 ; i<height+1; i++)
    {
        if (i<10)
        {
            printf("\t\t\t\t\t %d  |",i);/*drawing the column number*/
        }
        else
        {
            printf("\t\t\t\t\t %d |",i);
        }
        for (j = 1 ; j<width+1; j++)
        {
            if (arr[i][j].open == 0) /*not an open cell*/
            {

                if (arr[i][j].flag==1) /*drawing a flag*/
                {
                    colorGreen();
                    printf(" F ");
                    colorBlue();
                    printf("|");
                }

                else if (arr[i][j].question==1) /*drawing a question*/
                {
                    printf(" ? |");
                }
                else
                {
                    printf(" X |");/*drawing a closed cell*/
                }

            }
            else if (arr[i][j].open ==1)/*open cell*/
            {
                if(arr[i][j].mine==0)/*the cell does not contain a mine*/
                {
                    if (arr[i][j].flag == 1)/*a missed mine //drawn at the end of the game */
                    {
                        colorGray();
                        printf(" - ");
                        colorBlue();
                        printf("|");
                    }
                    else if (arr[i][j].minesArround==0)/*the cell is a blank and no mines around it*/
                    {
                        printf("   |");
                    }
                    else /*cell has a nearby mine*/
                    {
                        colorRed();
                        printf(" %d ",arr[i][j].minesArround);
                        colorBlue();
                        printf("|");
                    }
                }
                else if (arr[i][j].mineExplode==1) /*if the mine explodes*/
                {
                    colorExplode();
                    printf(" ! ");
                    colorBlue();
                    printf("|");
                }
                else if (arr[i][j].flag == 1 && arr[i][j].mine == 1)/*the cell had a mine but a flag was placed correctly*/
                {
                    colorGreen();
                    printf(" * ");
                    colorBlue();
                    printf("|");

                }
                else if (arr[i][j].mine==1)/*an unopened mine with no flags over it*/
                {
                    colorBlack();
                    printf(" M ");
                    colorBlue();
                    printf("|");
                }
            }
        }
        printf("\n\t\t\t\t\t    +");
        for (j = 1 ; j<width+1; j++)
        {
            printf("---+");
        }
        printf("\n");
    }
}
void checkmove(cell arr[MAX][MAX],int height,int width) /*the user's moves along the game*/
{
    int x, y;/*variables indicating the coordinates 'rows and columns' entered by the user*/
    int exitVar=0;/*a variable of initial value of zero if one means that the user chose exit so it
    doesn't allow the program to ask the user for row and column*/
    int saves=0;
    /*same as exit it indicates that the user entered save */
    h= &height;/*passing the address of the height and width to the global variables so it can be used in the threads*/
    w=&width;
    char moveType;/*indicating the user's choice*/
    pthread_t thread3;/*declaring a new thread*/
    threadnum1=1;/*initializing the thread key by 1*/
    pthread_create(&thread3,NULL,timerCheckMove,(void*)arr);/*creating the thread*/
    do
    {

        clock_t end_t = clock()/CLOCKS_PER_SEC;
        clear();
        draw(arr,height,width);
        UI(*start1_t,end_t);
        printf("\t\t\t\t\tO :open , Q : question , F : flag\n\t\t\t\t\tU : unmark , E : exit , S : save\n");
        printf("\t\t\t\t\tEnter the type of your move:");
        moveType = charScanner(1);/*scanning the user's choice*/
        int tmp =(moveType=='O'||moveType=='E'||moveType=='F'||moveType=='Q'||moveType=='S'||moveType=='U'||moveType=='o'||moveType=='e'||moveType=='f'||moveType=='q'||moveType=='s'||moveType=='u');
        if (!tmp)
        {
            printf("\t\t\t\t\tThis move is not valid\n\t\t\t\t\tTry again\n");
            Sleep(1500);
        }
    }
    while(!(moveType=='O'||moveType=='E'||moveType=='F'||moveType=='Q'||moveType=='S'||moveType=='U'||moveType=='o'||moveType=='e'||moveType=='f'||moveType=='q'||moveType=='s'||moveType=='u'));
    threadnum1=0;/*making the thread key equal 0 to make the thread terminate*/
    if (moveType=='E'||moveType=='e')/*user chose exit*/
    {
        printf("\t\t\t\t\tDo you really want to exit?\n\t\t\t\t\tY : yes\tN : no\n\t\t\t\t\tYour choice :");
        char choice;
        choice = charScanner(1);
        if(choice == 'Y' || choice == 'y')
        {
            char choice2 ;
            printf("\t\t\t\t\tDo you want to save?\n\t\t\t\t\tY : yes\tN : no\n\t\t\t\t\tYour choice :");
            choice2 = charScanner(1);
            if (choice2=='N'|| choice2 == 'n' )
            {
                /*this tells the main that the user entered exit and does n't want to save the game*/
                *exitCount=1;
                timeEnd=0;
            }
            else if(choice2=='Y'||choice2=='y')
            {
                /*taking the name of the user*/
                char* name;
                name = malloc(100);
                do
                {
                    printf("\t\t\t\t\tEnter the save name: ");
                    do
                    {
                        if(strlen(name)> 20)
                        {
                            printf("\t\t\t\t\tVery long name!! Try again: ");
                        }
                        else if(!strcmp(name,""))
                        {
                            printf("\t\t\t\t\tInvalid input!! Try again: ");
                        }
                        else if(name[0] == ' ')
                        {
                            printf("\t\t\t\t\tInvalid input!! Try again: ");
                        }
                        gets(name);
                    }
                    while(strlen(name)>20 || !strcmp(name, "") || name[0] == ' '); /*checks that the user entered a name with a length smaller than 20*/
                }
                while(saveChecker(name));
                /*saving the game*/
                save(arr,height,width,name);
                saveAttrib(arr,height,width,name);/*saving the attributes of the cells of the array*/
                *exitCount=1;/*this tells the main that the user exited and does not want to continue the game*/
                timeEnd=0;
            }
            else
            {
                printf("\t\t\t\t\tThis move is not valid\n\t\t\t\t\tTry again\n");
                /*the user has entered an in valid move and it calls it self again and
                this function will be terminated when it returns to it in the stack*/
                Sleep(1500);
                clock_t end_t = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }

        }
        else if(choice == 'N'||choice == 'n')
        {
            /*the user does n't want to exit*/
            exitVar=1;

        }
        else
        {
            printf("\t\t\t\t\tThis move is not valid\n\t\t\t\t\tTry again\n");
            exitVar=1;
            clock_t end_t = clock()/CLOCKS_PER_SEC;
            Sleep(1500);
            clear();
            draw(arr,height,width);
            UI(*start1_t,end_t);
            checkmove(arr,height,width);
        }

    }
    else if(moveType == 'S'||moveType == 's')
    {
        char* name;
        name = malloc(100);
        do
        {
            printf("\t\t\t\t\tEnter the save name: ");
            do
            {
                if(strlen(name)> 20)
                {
                    printf("\t\t\t\t\tVery long name!! Try again: ");
                }
                else if(!strcmp(name,""))
                {
                    printf("\t\t\t\t\tInvalid input!! Try again: ");
                }
                else if(name[0] == ' ')
                {
                    printf("\t\t\t\t\tInvalid input!! Try again: ");
                }
                gets(name);
            }
            while(strlen(name)>20 || !strcmp(name, "") || name[0] == ' ');
        }
        while(saveChecker(name));
        save(arr,height,width,name);
        saveAttrib(arr,height,width,name);
        saves++;/*indicates that the user chose is the save so it wont ask the user for a row or column*/
        clock_t end_t = clock()/CLOCKS_PER_SEC;
        clear();
        draw(arr,height,width);
        UI(*start1_t,end_t);
        checkmove(arr,height,width);
    }
    if (!*exitCount&&!exitVar&&!saves)
    {
        pthread_t threadC;/*creating thread*/
        threadnum3=1;/*the thread key*/
        pthread_create(&threadC,NULL,timerRow,(void*)arr);
        clock_t end_t = clock()/CLOCKS_PER_SEC;
        clear();
        draw(arr,height,width);
        UI(*start1_t,end_t);
        printf("\t\t\t\t\tPlease enter the row number   :");
        while((scanf(" %d",&x) != 1)||(x > height || x < 1)||getchar() != '\n')
        {
            printf("\t\t\t\t\tthis is not a valid choice\n\t\t\t\t\ttry again ",height);
            clock_t end_t1 = clock()/CLOCKS_PER_SEC;
            clear();
            draw(arr,height,width);
            UI(*start1_t,end_t);
            printf("\t\t\t\t\tThe row must be between 1 and %d \n\t\t\t\t\tPlease enter the row number: ",height);
            while(getchar() != '\n');
        }
        threadnum3=0;
        pthread_t thread2;/*creating another thread*/
        threadnum2=1;
        pthread_create(&thread2,NULL,timerColumn,(void*)arr);
        clock_t end_t2 = clock()/CLOCKS_PER_SEC;
        clear();
        draw(arr,height,width);
        UI(*start1_t,end_t);
        printf("\t\t\t\t\tPlease enter the column number: ");
        while((scanf(" %d",&y) != 1)||(y > width || y < 1)||getchar() != '\n')
        {
            printf("\t\t\t\t\tthis is not a valid choice\n\t\t\t\t\ttry again ",width);
            clock_t end_t3 = clock()/CLOCKS_PER_SEC;
            clear();
            draw(arr,height,width);
            UI(*start1_t,end_t);
            printf("\t\t\t\t\tThe column must be between 1 and %d \n\t\t\t\t\tPlease enter the column number: ",height);
            while(getchar() != '\n');
        }
        threadnum2=0;
        if (moveType=='O'||moveType == 'o')
        {
            if (arr[x][y].open==1)/*if the cell is already opened checks the number of flags surrounding this certain cell
                if equal or greater than the number of mines around the cell it opens all the surrounding closed cells*/
            {
                if (arr[x][y].minesArround!=0)
                 {
                    int i,j,flagCount=0;
                    for(i=-1; i<2; i++ )
                    {
                        for(j=-1; j<2; j++)
                        {
                            if(arr[x+i][y+j].flag==1&&(i!=0||j!=0))
                            {
                                flagCount++;/*counts the flags around*/
                            }
                        }
                    }
                    if (flagCount < arr[x][y].minesArround||flagCount > arr[x][y].minesArround)
                    {
                        printf("\t\t\t\t\tNumber of flags not equal the minesAround!\n\t\t\t\t\ttry again\n");
                        clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                        Sleep(2500);
                        clear();
                        draw(arr,height,width);
                        UI(*start1_t,end_t);
                        checkmove(arr,height,width);
                    }
                    else
                    {
                        /*calls the function that opens the surrounding  and increases the moves done*/
                        flagOpen(arr,height,width,x,y);
                        if (opened)
                        {
                            movesDone++;
                            opened = 0;
                        }
                        else
                        {
                            printf("\t\t\t\t\tAll of its surrounding is opened!\n\t\t\t\t\ttry again\n");
                            Sleep(1500);

                        }
                    }
                 }
                 else
                {
                    printf("\t\t\t\t\tThis is an opened empty cell !\n\t\t\t\t\ttry again\n");
                    clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                    Sleep(1500);
                    clear();
                    draw(arr,height,width);
                    UI(*start1_t,end_t);
                    checkmove(arr,height,width);
                }

            }
            else if (arr[x][y].flag==1)
            {
                /*if it it is flagged it should not open*/
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].question==1)
            {
                /*if it it is flagged it should not open*/
                printf("\t\t\t\t\tThis one is suspicious  !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else
            {
                /*if the move is valid it increases the moves done and opens the cell*/
                movesDone++;
                openCell(arr,height,width,x,y);
            }
        }
        else if (moveType=='Q' || moveType == 'q')
        {
            /*the user attempted to put a question*/
            if (arr[x][y].open==1)/*its not allowed to add a question on an opened cell*/
            {
                printf("\t\t\t\t\tThis one is already opened !\n\t\t\t\t\ttry again\n");
                /*calls it self again*/
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].flag==1)/*its not allowed to add a question on an flagged cell*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].question==1)/*its not allowed to add a question on an already questioned cell*/
            {
                printf("\t\t\t\t\tThis one already has a question mark !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else
            {
                /*puts the question and increases the number of moves done*/
                movesDone++;
                questionsPlaced++;
                arr[x][y].question=1;
            }
        }
        else if (moveType=='F'||moveType == 'f')
        {
            if(remainOfFlags == 0)/*if the number of flags placed is maximum it refuses to print another*/
            {
                printf("\t\t\t\t\tYou can not place any more flags!\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].open==1)/*its not allowed to add a flag on an opened cell*/
            {
                printf("\t\t\t\t\tThis one is already opened !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].flag==1)/*its not allowed to add a flag on an flagged cell*/
            {
                printf("\t\t\t\t\tThis one is already flagged !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].question==1)/*its not allowed to add a flag on a questioned cell*/
            {
                printf("\t\t\t\t\tThis one already has a question mark !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else
            {
                /*puts a flag and increases the moves done*/
                movesDone++;
                remainOfFlags --;
                flagsPlaced++;
                arr[x][y].flag = 1;
            }
        }
        else if (moveType=='U'||moveType=='u')
        {
            if (arr[x][y].open==1)/*it is not allowed to unmark an opened cell*/
            {
                printf("\t\t\t\t\tThis one is already opened !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else if (arr[x][y].flag==0&&arr[x][y].question==0)/*it is not allowed to unmark a non flagged nor questioned cell*/
            {
                printf("\t\t\t\t\tThis one is not marked !\n\t\t\t\t\ttry again\n");
                Sleep(1500);
                clock_t end_t2 = clock()/CLOCKS_PER_SEC;
                clear();
                draw(arr,height,width);
                UI(*start1_t,end_t);
                checkmove(arr,height,width);
            }
            else
            {
                /*removes the flag or the question*/
                movesDone++;
                if(arr[x][y].question == 0)
                {
                    /*increases the flags remaining and decreases the flags placed*/
                    remainOfFlags ++;
                    flagsPlaced--;
                    arr[x][y].flag=0;
                }
                else
                {
                    /*decreases the questions placed number*/
                    questionsPlaced--;
                    arr[x][y].question=0;
                }
            }
        }
    }
}
void pass(int *p,clock_t *q, int*s, int*r)/*function that the addresses of the height , width , exitcount and the starting time from the main to the library*/
{
    exitCount = p;
    start1_t = q;
    heightForLoad = s;
    widthForLoad = r;
}
int saveChecker(char* name) /*checks the save directory for the given name*/
{
    int ret;
    char help1[20]="saves\\"; /*directory management*/
    char help2[20]="saves\\"; /*directory management*/
    char* dir; /*directory management*/
    dir = &help1; /*creating the directory*/
    strcat(dir, name);
    strcat(dir, ".txt");
    FILE* check;
    check = fopen(dir,"r"); /*opens the file*/
    if(check != NULL) /*the file can be opened // File exists*/
    {
        printf("\t\t\t\t\tFile exists!!\n");
        printf("\t\t\t\t\tDo you wish to overwrite??\n");
        printf("\t\t\t\t\tY: Yes, N: No : ");
        char moveType;
        moveType = charScanner(1);
        if(moveType == 'Y') /*overwrite the file*/
        {
            fclose(check);
            ret = remove(dir); /*removing the save file*/
            dir = &help2;
            strcat(dir,name);
            strcat(dir, ".csv");
            ret = remove(dir); /*removing the attributes file*/
            return 0; /*the new file will be saved*/
        }
        else if(moveType = 'N') /*user will keep the old file*/
        {
            fclose(check);
            return 1; /*user is asked to enter another save name*/
        }
        else
        {
            fclose(check);
            printf("\t\t\t\t\tInvalid input!");
            return 1;
        }
    }
    else
    {
        return 0;
    }
}
void save(cell arr[MAX][MAX],int height,int width, char* name)/*saving the .txt file*/
{
    int i, ret;
    char* dir;
    char help[100]="saves\\"; /*directory management*/
    char oldname[] = "saves\\scores.txt"; /*name changer*/
    for(i=0; i<strlen(name); i++) /*changing the name to lower case*/
    {
        name[i] = tolower(name[i]);
    }
    FILE* saving;
    saving = fopen("saves\\scores.txt","w"); /*opening the file in the directory*/
    fprintf(saving,"%d\n%d\n%d\n%d\n%d\n%d\n%.1f",height,width,movesDone,remainOfFlags,questionsPlaced,flagsPlaced,diff_t); /*saving the desired values*/
    fclose(saving);
    dir = &help;
    strcat(dir,name);
    strcat(dir, ".txt");
    ret = rename(oldname, dir); /*renaming the old file with the user's entry name*/
    free(dir);
}
void saveAttrib(cell arr[MAX][MAX],int height,int width, char* name) /*saving the .csv file*/
{
    int i, j, ret;
    char* dir;
    char help[100]="saves\\"; /*directory management*/
    char oldname[] = "saves\\attrib.csv"; /*name changer*/
    for(i=0; i<strlen(name); i++) /*changing the name to lower case*/
    {
        name[i] = tolower(name[i]);
    }
    FILE* attrib;
    attrib = fopen("saves\\attrib.csv", "w"); /*opening the file in the directory*/
    for(i=0; i<height+2; i++) /*scanning the attributes of each cell in a comma separated value file for easier retrieve and debug*/
    {
        for(j=0; j<width+2; j++)
        {
            fprintf(attrib,"%d,%d,%d,%d,%d,%d,%d\n",arr[i][j].mine,arr[i][j].open,arr[i][j].banned,arr[i][j].question,arr[i][j].flag,arr[i][j].minesArround,arr[i][j].mineExplode);
        }
    }
    fclose(attrib);
    dir = &help;
    strcat(dir,name);
    strcat(dir,".csv");
    ret = rename(oldname, dir); /*renaming the file to user's entry name*/
    free(dir);
}
int loadChecker(char* name) /*checks the directory for the files*/
{
    char enter;
    char* dir;
    char* back;
    char help[100] = "saves\\"; /*directory management*/
    dir = &help;
    strcat(dir, name);
    strcat(dir, ".txt");
    FILE* checker;
    checker = fopen(dir,"r"); /*opening the directory file*/
    if(checker!=NULL) /*file can be opened then it exists*/
    {
        fclose(checker);
        return 0; /*returns to loading the file*/
    }
    else /*the user is asked to enter the name of an existing file*/
    {
        DIR* folder; /*opens the folder*/
        struct dirent *ent;
        if((folder = opendir("saves\\"))!=NULL)
        {
            int i=0;             /*shows the user the available file names only*/
            printf("\t\t\t\t\tThe following is only available to load\n\n");
            while((ent = readdir(folder)) != NULL)
            {
                char* stringConvert;
                char stringTo[20] = {};
                stringConvert = malloc(100); /*making the name more clear to the user by removing .txt part*/
                i++;
                if(i%2 == 0 && i>2) /*avoiding printing the .csv file name*/
                {
                    stringConvert = ent->d_name;
                    int j;
                    strncpy(stringTo,stringConvert,strlen(stringConvert)-4);
                    printf("\t\t\t\t\t  ");
                    for(j=0; j<strlen(stringTo); j++)
                    {
                        printf("%c",stringTo[j]); /*printing the name*/
                    }
                    printf("\n");
                }
                free(stringConvert);
            }
            printf("\n");
            closedir(folder); /*closing the folder*/
        }
        printf("\t\t\t\t\tPress Enter to continue");
        enter = charScanner(2);
        return 1; /*returning to ask the user for another name*/
    }
    free(dir);
}
void load(cell arr[MAX][MAX], char* name) /*loading a previously existing game*/
{
    int i, j, height, width;
    int ret;
    char* dir;
    char help1[100] = "saves\\"; /*directory management*/
    char help2[100] = "saves\\"; /*directory management*/
    for(i=0; i<strlen(name); i++) /*changes the name to lower case characters*/
    {
        name[i] = tolower(name[i]);
    }
    FILE* loading;
    dir = &help2;
    strcat(dir, name);
    strcat(dir,".txt");
    loading = fopen(dir, "r"); /*opens the file directory*/
    fscanf(loading,"%d%d%d%d%d%d%d",&height,&width,&movesDone,&remainOfFlags,&questionsPlaced,&flagsPlaced,&timeEnd); /*scans the values stored in the file*/
    fclose(loading);
    ret = remove(help2);
    *heightForLoad = height; /*passes the value to the main for the next functions*/
    *widthForLoad = width; /*passes the value to the main for the next functions*/
    dir = &help1;
    strcat(dir, name);
    strcat(dir,".csv");
    loading = fopen(dir, "r");
    for(i=0; i<height+2; i++) /*scans the values of each attribute for each cell for the .csv file*/
    {
        for(j=0; j<width+2; j++)
        {
            fscanf(loading,"%d,%d,%d,%d,%d,%d,%d\n",&arr[i][j].mine,&arr[i][j].open,&arr[i][j].banned,&arr[i][j].question,&arr[i][j].flag,&arr[i][j].minesArround,&arr[i][j].mineExplode);
        }
    }
    fclose(loading);
    ret = remove(help1);
    free(dir);
}
void win(cell grid[MAX][MAX],int height,int width) /*the user has won the game*/
{
    clear();
    char enter = '0';
    printf("\n\n\t\t\t\t\t\t** YOU WIN **\n");
    int i, j;
    for(i=1; i<height+1; i++) /*change the attributes to open the grid*/
    {
        for(j=1; j<width+1; j++)
        {
            if(grid[i][j].open == 0)
            {
                grid[i][j].flag = 1;
            }
        }

    }
    draw(grid,height,width); /*opens the grid*/
    scoresheetSave(height,width); /*checks the score*/
    printf("\n\t\t\t\t\tPress enter to continue.");
    enter = charScanner(2);
    clear();
    menu();/*returns to main menu*/
    printf("\t\t\t\t\tMake your choice :");
    timeEnd=0;
}
int ifWin(cell arr[MAX][MAX],int height,int width,int minesNumber) /*checks whether the user has won or not*/
{
    /*if the number of closed cells equals the number of mines the user wins
    the lose test is performed first */
    int i,j,closed=0;
    for(i = 1 ; i<height+1; i++)
    {
        for (j = 1 ; j<width+1; j++)
        {
            if(arr[i][j].open==0)
            {
                closed++;/*counts the closed cells*/
            }
        }
    }
    if (closed == minesNumber)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}
void lose(cell grid[MAX][MAX],int height,int width) /*the user has lost the game*/
{
    clear();
    char enter = '0';
    printf("\n\n\t\t\t\t\t\t**YOU LOSE**\n");
    int i, j;
    for(i=1; i<height+1; i++) /*changes the attributes to open the grid*/
    {
        for(j=1; j<width+1; j++)
        {
            grid[i][j].open = 1;
        }
    }
    draw(grid,height,width); /*draws the grid*/
    printf("\n\t\t\t\t\tPress enter to continue.");
    enter = charScanner(2);
    clear();
    menu(); /*returns to main menu*/
    printf("\t\t\t\t\tMake your choice :");
    timeEnd=0;
}
int ifLose(cell arr[MAX][MAX],int height,int width) /*checks whether the user has lost or not*/
{
    int i,j;/*checks if there is an opened cell containing a mine*/
    for(i = 1 ; i<height+1; i++)
    {
        for (j = 1 ; j<width+1; j++)
        {
            if(arr[i][j].mine==1&&arr[i][j].open==1)
            {
                return 1;
            }
        }
    }
    return 0;

}
void openCell(cell arr[MAX][MAX],int height,int width,int x,int y)/*opens the requested cell*/
{
    if (arr[x][y].banned==1)
    {
        /*no action will be taken on padding*/
    }
    else if (arr[x][y].mine==1)/*if the cell contain a mine then this cell will be opened and will be an exploded mine*/
    {
        arr[x][y].open=1;
        arr[x][y].mineExplode=1;
    }
    else if (arr[x][y].minesArround>0)/*if the cell has mines around it is opened*/
    {
        arr[x][y].open = 1;
    }
    else
    {
        arr[x][y].open = 1;
        int i,j;
        for(i=-1; i<2; i++ )
        {
            for(j=-1; j<2; j++)
            {
                if(arr[x+i][y+j].flag==0&&arr[x+i][y+j].banned==0&&arr[x+i][y+j].open==0)/*if it is empty cell it opens all the unbanned and unflagged cells*/
                {
                    arr[x+i][y+j].open=1;
                    if(arr[x+i][y+j].question==1)
                    {
                        questionsPlaced--;/*removing questions and decreases the number of question placed*/
                        arr[x+i][y+j].question=0;
                    }
                    openCell(arr,height,width,x+i,y+j);
                }
            }
        }
    }
}
void flagOpen(cell arr[MAX][MAX],int height,int width,int x,int y)/*opens the surrounding blank cells*/
{
    int i, j;
    opened = 0;
    /*opens all the unopened unflagged cells around the current*/
    for(i=-1; i<2; i++)
    {
        for(j=-1; j<2; j++)
        {
            if(arr[x+i][y+j].open==0&&arr[x+i][y+j].flag==0&&arr[x+i][j+y].banned==0&&(i!=0||j!=0))
            {
                openCell(arr,height,width,x+i,y+j);
                opened ++;
            }
        }
    }
}
void UI(clock_t start_t, clock_t end_t) /*prints for the user the number of moves done, time, and other important informations*/
{
    double seconds; /*variables indicating minutes and seconds*/
    int minutes;
    if (timeEnd == 0) /*no time coming from load*/
    {
        diff_t = end_t-start_t;
        minutes= diff_t/60;
        seconds = (int)diff_t%60;
    }
    else /*continuing over load time*/
    {
        static int i = 1;
        if(i==1) /*reset the time*/
        {
            start_t=0;
            end_t=0;
            i=0;
        }
        diff_t = timeEnd + end_t - start_t ; /*calculates the time*/
        minutes= diff_t/60;
        seconds = (int)diff_t%60;
    }



    /*printing and changing the colors several times */

    printf("\n\t\t\t\t\tMoves : ");
    colorPurple();
    printf("%d",movesDone);
    colorBlue();
    printf("\t Flags Remaining: ");
    colorPurple();
    printf("%d\t",remainOfFlags);
    colorBlue();
    printf("\n\t\t\t\t\tTime  : ");
    colorPurple();
    if (seconds<10)/*if seconds < 9 print 0 next to it*/
    {
        printf("%d : 0%.0lf \t ",minutes,seconds);
    }
    else
    {
        printf("%d : %.0lf \t ",minutes,seconds);
    }
    colorBlue();
    printf("Flags Placed   : ");
    colorPurple();
    printf("%d\n",flagsPlaced);
    colorBlue();
    printf("\t\t\t\t\tQuestions Placed   : ");
    colorPurple();
    printf("%d\n\n",questionsPlaced);
    colorBlue();
}
void logger(cell arr[MAX][MAX],int height,int width) /*prints the off grid to help debugging*/
{
    int i,j;
    FILE* fileLog;
    fileLog = fopen("log.txt","w"); /*opens the file*/
    fprintf(fileLog,"    ");
    for (j = 1 ; j<width+1; j++) /*draws the grid*/
    {
        if(j<10)
        {
            fprintf(fileLog,"  %d ",j);
        }
        else
        {
            fprintf(fileLog," %d ",j);
        }
    }
    fprintf(fileLog,"\n    +");
    for (j = 1 ; j<width+1; j++)
    {
        fprintf(fileLog,"---+");
    }
    fprintf(fileLog,"\n");
    for(i = 1 ; i<height+1; i++)
    {
        if(i<10)
        {
            fprintf(fileLog," %d  |",i);
        }
        else
        {
            fprintf(fileLog," %d |",i);
        }
        for (j = 1 ; j<width+1; j++)
        {
            if (arr[i][j].flag==1 && arr[i][j].mine == 1)/*draws a safe flag*/
            {
                fprintf(fileLog," F |");
            }
            else if (arr[i][j].question==1)/*draws a question*/
            {
                fprintf(fileLog," ? |");
            }
            else if(arr[i][j].mine==0)/*the cell does not contain a mine*/
            {
                if (arr[i][j].flag == 1)
                {
                    fprintf(fileLog," - |"); /*draws a missed flag*/
                }
                else
                {
                    fprintf(fileLog,"   |");
                }
            }
            else if (arr[i][j].mineExplode==1) /*draws an exploded mine*/
            {
                fprintf(fileLog," ! |");
            }

            else if (arr[i][j].mine==1) /*draws an untouched mine*/
            {
                fprintf(fileLog," * |");
            }
            else
            {
                fprintf(fileLog,"   |");
            }

        }
        fprintf(fileLog,"\n    +");

        for (j = 1 ; j<width+1; j++)
        {
            fprintf(fileLog,"---+");
        }
        fprintf(fileLog,"\n");
    }
    fclose(fileLog);
}
void scoresheetSave(int height, int width) /*manages the score sheet*/
{
    int saveLimit = 0;
    double previousScore;
    int found= 1, i=0, j=0;
    char* back;
    char* name;
    char* tempName;
    char* compare;
    back = malloc(100);           /*string holders*/
    name = malloc(100);
    tempName = malloc(100);
    compare = malloc(100);
    do
    {
        if(strlen(name) > 20)
        {
            printf("\t\t\t\t\tVery long name!!\n");
        }
        else if(!strcmp(name,"") || name[0] == ' ')
        {
            printf("\t\t\t\t\tInvalid input!\n");
        }
        printf("\t\t\t\t\tEnter your name: "); /*user enter his name*/
        gets(name);
    }
    while(strlen(name)>20 || !strcmp(name,"") || name[0] == ' ');
    fflush(stdin);

    if (diff_t<1) /*assigns time if the user has won on a single move*/
    {
        diff_t=1;
    }
    double sec ;
    int min;
    min= diff_t/60;
    sec = (int)diff_t%60;
    double gameScore = (pow(height,4)*pow(width,4))/(movesDone*diff_t);  /*calculates the score*/
    printf("\t\t\t\t\tYour score: %.2lf\n\t\t\t\t\tYour time: ", gameScore);
    if (sec<10)/*if seconds < 9 print 0 next to it*/
    {
        printf("%d : 0%.0lf \n",min,sec);
    }
    else
    {
        printf("%d : %.0lf \n",min,sec);
    }
    FILE* scoreSheet;
    scoreSheet = fopen("scores.txt", "r"); /*opens the score sheet*/
    while(fgets(back,100,scoreSheet) != NULL)
    {
        saveLimit++; /*checks the number of saves already existing in the file*/
    }
    fclose(scoreSheet);

    memcpy(tempName, name, 100); /*copies the name to tempName in order to change it safely*/

    for(j=0; j<strlen(tempName); j++)
    {
        tempName[j] = tolower(tempName[j]); /*changing the name to lower case*/
    }
    scoreSheet = fopen("scores.txt", "r"); /*opening the score sheet again*/
    for(i=0; i<saveLimit; i++) /*scans a name each turn of the loop*/
    {
        fscanf(scoreSheet,"%s %lf", compare,&previousScore); /*scans the name to be compared to*/
        for(j=0; j<strlen(compare); j++)
        {
            compare[j] = tolower(compare[j]); /*changes the compare name to lower case*/
        }
        found = strcmp(tempName, compare); /*compares both names*/
        if(found == 0)
        {
            break; /*the name is found*/
        }
    }
    fclose(scoreSheet);
    if(found != 0 && saveLimit<10) /*the name is not found and there is a space to save an entry*/
    {
        scoreSheet = fopen("scores.txt", "a"); /*opens the score sheet to append a value*/
        fseek(scoreSheet,0,SEEK_END); /*seeks the cursor to the end of the file*/
        fprintf(scoreSheet, " %s", name); /*stores the name*/
        fprintf(scoreSheet, "  %.2lf",gameScore);/*stores the score*/
        fprintf(scoreSheet, "\n");
        fclose(scoreSheet);
    }
    else if(found != 0 && saveLimit==10) /*the name is not found and there is no space to save...we will remove the lowest score*/
    {
        double playerScore;
        int ret,i, minScore, indexer = 0;
        double scores[10]; /*getting all the scores in the array*/
        char oldname[] = "scores1.txt";/*name changer*/
        char newname[] = "scores.txt";/*name changer*/
        FILE* tempFile; /*creating a temporary file*/
        scoreSheet = fopen("scores.txt", "r");/*reads from the score sheet*/
        tempFile = fopen("scores1.txt", "w");/*writes int the temp file*/
        for(i=0; i<10; i++)
        {
            fscanf(scoreSheet," %s %lf",back, &scores[i]); /*putting the scores in the array*/
        }
        minScore = scores[0];
        for(i=1; i<10; i++) /*getting the minimum scores index*/
        {
            if(minScore>scores[i])
            {
                minScore = scores[i];
                indexer = i;
            }
        }
        fseek(scoreSheet,0,SEEK_SET); /*seeking the cursor to the beginning of the file*/
        for(i=0; i<10; i++) /*copying all the data to the temporary files except the one with the minimum score index*/
        {
            if(i == indexer)
            {
                fscanf(scoreSheet, " %s %lf",back, &playerScore); /*skipping the minimum score index*/
                continue;
            }
            else
            {
                /*copying the data to the temporary file*/
                fscanf(scoreSheet, " %s %lf",back, &playerScore);
                fprintf(tempFile, " %s %.2lf",back, playerScore);
                fprintf(tempFile, "\n");
            }
        }
        fclose(scoreSheet);
        fclose(tempFile);
        ret = remove(newname); /*removing the score sheet*/
        ret = rename(oldname, newname); /*renaming the temporary file with the old score sheet name*/
        scoreSheet = fopen("scores.txt", "a"); /*opening the new file and appending the new value to it*/
        fseek(scoreSheet,0,SEEK_END);
        fprintf(scoreSheet, " %s", name);
        fprintf(scoreSheet, "  %.2lf",gameScore);
        fprintf(scoreSheet, "\n");
        fclose(scoreSheet);
    }
    else if(found == 0 && previousScore < gameScore) /*the name is found and his score is greater than the saved one....we will automatically store the higher one*/
    {
        double playerScore;
        int ret;
        char oldname[] = "scores1.txt"; /*name changer*/
        char newname[] = "scores.txt"; /*name changer*/
        FILE* tempFile;
        scoreSheet = fopen("scores.txt", "r"); /*reads from the old file*/
        tempFile = fopen("scores1.txt", "w"); /*writes in the new file*/
        for(j=0; j<saveLimit; j++)
        {
            if(j==i) /*copies the data except the found name index*/
            {
                fscanf(scoreSheet, " %s %lf", back, &playerScore);
                continue;
            }
            else
            {
                fscanf(scoreSheet, " %s %lf", back, &playerScore);
                fprintf(tempFile, " %s %.2lf", back, playerScore);
                fprintf(tempFile, "\n");
            }
        }
        fclose(scoreSheet);
        fclose(tempFile);
        ret = remove(newname); /*removes the old file*/
        ret = rename(oldname, newname); /*renames the new file with the older one*/
        scoreSheet = fopen("scores.txt", "a"); /*appends the new data to the end of the file*/
        fseek(scoreSheet,0,SEEK_END);
        fprintf(scoreSheet, " %s", name);
        fprintf(scoreSheet, "  %.2lf",gameScore);
        fprintf(scoreSheet, "\n");
        fclose(scoreSheet);
    }
    else /*the name is find but his score is lower than the one saved*/
    {
        printf("\t\t\t\t\tThis score is not your best....Good luck next time");
    }
    free(back);
    free(name);
    free(compare);
    free(tempName);
}
void scoresheetSorter() /*sorts the score sheet form in a decreasing manner*/
{
    int saveLimit = 0, i, swapped;
    char* back;
    char* stringTemp;
    back = malloc(100);
    stringTemp = malloc(100); /*temporary string holder*/
    FILE* scoreSheet;
    scoreSheet = fopen("scores.txt", "r"); /*reads from the score sheet*/
    while(fgets(back,100,scoreSheet) != NULL)
    {
        saveLimit++; /*counts the number of saved entities*/
    }
    fseek(scoreSheet,0,SEEK_SET); /*seeks the begining of the file*/
    char* str[saveLimit]; /*array of strings*/
    double scoresArray[saveLimit]; /*array of strings*/
    for(i=0; i<saveLimit; i++)
    {
        str[i] = malloc(100); /*allocating the string array*/
    }
    for(i=0; i<saveLimit; i++)
    {
        fscanf(scoreSheet, " %s %lf", str[i], &scoresArray[i]); /*scan the two arrays parallel to each other*/
    }
    while(1) /*bubble sorting both arrays parallel to each other*/
    {
        swapped = 0;
        for(i=0; i<saveLimit-1; i++)
        {
            if(scoresArray[i] < scoresArray[i+1])
            {
                double scoreTemp;
                scoreTemp = scoresArray[i+1]; /*swapping the score*/
                scoresArray[i+1] = scoresArray[i];
                scoresArray[i] = scoreTemp;
                stringTemp = str[i+1]; /*swapping the string with the same index of the score*/
                str[i+1] = str[i];
                str[i] = stringTemp;
                swapped = 1;
            }
        }
        if(swapped == 0)
        {
            break;
        }
    }
    fclose(scoreSheet);
    scoreSheet = fopen("scores.txt", "w"); /*reopens the file to rewrite the data*/
    clear();
    for(i=0; i<saveLimit; i++)
    {
        /*writes the name and score parallel to each other*/
        fprintf(scoreSheet, " %s", str[i]);
        fprintf(scoreSheet, "  %.2lf",scoresArray[i]);
        fprintf(scoreSheet, "\n");
    }
    fclose(scoreSheet);
    for(i=0; i<saveLimit; i++)
    {
        free(str[i]);
    }
    free(stringTemp);
    free(back);
}
void scoresheetLoad() /*loading the score sheet to the user*/
{
    scoresheetSorter();
    int saveLimit = 0, i;
    char* back;
    back = malloc(100);
    FILE* scoreSheet;
    scoreSheet = fopen("scores.txt", "r"); /*opens the file to read from it*/
    while(fgets(back,100,scoreSheet) != NULL)
    {
        saveLimit++; /*counts the number of save entities*/
    }
    fseek(scoreSheet,0,SEEK_SET); /*seeks the begining of the file*/
    printf("\n");
    for(i=0; i<saveLimit; i++)
    {
        printf("\t\t\t\t\t");
        fgets(back,100,scoreSheet); /*gets a single complete line from the file*/
        puts(back); /*prints it to the user*/
    }
    fclose(scoreSheet);
    free(back);
}
void clearScores() /*clears the score sheet*/
{
    int ret;
    char oldname[] = "scores.txt";
    char newname[] = "scores1.txt";
    ret = remove(oldname); /*deletes the record*/
    ret = rename(newname, oldname); /*creates a new blank one*/
}
void goodBye(void)
{
    clear();
    system("COLOR FC");
    char c[]="\n\n\t\t\t\t\tHoping you had a good time  :D\n\t\t\t\t\t     Come again later ;)\n\n";
    int i;
    for(i = 0 ; i<strlen(c); i++)
    {
        printf("%c",c[i]);
        Sleep(60);
    }
    system("COLOR A3");
    Sleep(400);
    system("COLOR D5");
    Sleep(400);
    system("COLOR E1");
    Sleep(400);
    system("COLOR C8");
    Sleep(400);
    system("COLOR B9");
    Sleep(400);
    system("COLOR F1");
    Sleep(400);
}
